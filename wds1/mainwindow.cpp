#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QList>
#include <QSerialPortInfo>
#include <QDateTime>
#include "wykres.h"

/*!
 * \file
 * \brief Deklaracja klasy MainWindow
 */

class Viewer;

/*!
 * \brief Konstruktor klasy MainWindow
 *
 * Inicjalizuje warstwę graficzną, tworzy połączenia między klasą a jej dziećmi.
 * \param[in] parent - rodzic klasy
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->device = new QSerialPort(this);
    setWindowTitle("Wizualizacja dynamiki cieczy");
    tab_zakladka * zakladka1 = new tab_zakladka(this);
    QObject::connect(zakladka1, SIGNAL(sigColor(int)), this, SLOT(colorChanged(int)));
    QObject::connect(zakladka1, SIGNAL(sigVelocity(double)), this, SLOT(velocityChanged(double)));
    ui->horizontalLayout->addWidget(zakladka1);
    roll=0;
    pitch=0;
}

/*!
 * \brief Destruktor klasy MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief Czyta informacje z portu szeregowego połączonego urządzenia
 *
 * Metoda odczytuje dane pojawiające się na serialu, wywołuje funkcje sprawdzające integralność danych.
 * Jeżeli dane są spójne zostają one przypisane do odpowiadających wartości w oknie obiekcie GLWindow.
 * Wywołuje metodę WykresWindow dodającą wartości do serii pomiarów.
 */
void MainWindow::readFromPort()
{
    while(this->device->canReadLine()) {
       QString line = this->device->readLine();
       QString terminator = "\r";
       int pos = line.lastIndexOf(terminator);
       std::string str = line.left(pos).toStdString();
       const char* p = str.c_str();
       if(ParseDataFrame(p,pitch,roll))
       {
           this->addToLogs(" x: " + QString::number(roll)+" y: "+QString::number(pitch));
           ui->widget->ax=(roll);
           ui->widget->ay=(pitch);
           oknoWykresow.addValues(roll, pitch);
           if(pitch<0)
               ui->widget->axp=-1;
           else
               ui->widget->axp=1;
           if(roll<0)
               ui->widget->ayp=1;
           else
               ui->widget->ayp=-1;
           ui->widget->update();
       }
       else
           this->addToLogs("Nieprawidłowe dane");
     }
}

/*!
 * \brief Wyszukuje dostępne urządzenia
 *
 * Wyszukuje dostępne urządzenia oraz wypełnia nimi comboBox.
 */
void MainWindow::on_pushButtonSearch_clicked()
{
   this->addToLogs("Szukam urządzeń...");
    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    for(int i = 0; i < devices.count(); i++) {
      this->addToLogs("Znalazłem urządzenie: " + devices.at(i).portName() + " " + devices.at(i).description());
      ui->comboBoxDevices->addItem(devices.at(i).portName()+"\t"+devices.at(i).description());
    }
    if(devices.count() != 0) {
        ui->pushButtonConnect->setDisabled(false);
        ui->comboBoxDevices->setDisabled(false);
    }
}

/*!
 * \brief Dodaje tekst do logów
 * \param[in] message - tekst do dodania
 */
void MainWindow::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textEditLogs->append(currentDateTime + "\t" + message);
}

/*!
 * \brief Łączy z wybranym urządzeniem
 *
 * Łączy z urządzeniem wybranym z comboBox.
 * Przypisuje parametry połączenia takie jak prędkość transmisji, parzystość czy ilość przesyłanych bitów.
 */
void MainWindow::on_pushButtonConnect_clicked()
{
    if(ui->comboBoxDevices->count() == 0) {
      this->addToLogs("Nie wykryto żadnych urządzeń!");
      return;
    }

    QString portName = ui->comboBoxDevices->currentText().split("\t").first();
    this->device->setPortName(portName);
    if(!device->isOpen()){
    if(device->open(QSerialPort::ReadWrite)) {
      this->device->setBaudRate(QSerialPort::Baud9600);
      this->device->setDataBits(QSerialPort::Data8);
      this->device->setParity(QSerialPort::NoParity);
      this->device->setStopBits(QSerialPort::OneStop);
      this->device->setFlowControl(QSerialPort::NoFlowControl);
      connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));
      this->addToLogs("Otwarto port szeregowy.");
      ui->pushButtonConnect->setDisabled(true);
      ui->pushButtonSearch->setDisabled(true);
      ui->comboBoxDevices->setDisabled(true);
      ui->pushButtonDisconnect->setDisabled(false);
      this->addToLogs("Otwarcie porty szeregowego się nie powiodło!");
    }
    }
    else{
        this->addToLogs("Port jest już otwarty");
    }
}

/*!
 * \brief Zamyka połączenie z urządzeniem
 */
void MainWindow::on_pushButtonDisconnect_clicked()
{
    if(this->device->isOpen()) {
      this->device->close();
      this->addToLogs("Zamknięto połączenie.");
      ui->pushButtonSearch->setDisabled(false);
      ui->pushButtonConnect->setDisabled(false);
      ui->comboBoxDevices->setDisabled(false);
      ui->pushButtonDisconnect->setDisabled(true);
    } else {
      this->addToLogs("Port nie jest otwarty!");
      return;
    }
}

/*!
 * \brief Zamyka okno aplikacji
 */
void MainWindow::on_pushButtonClose_clicked()
{
    MainWindow::close();
}

/*!
 * \brief Zmienia wartość poziomu wody
 *
 * Zmienia wartość poziomu wody, wywołuje metodę zmiany poziomu klasy GLWidget.
 * \param[in] position - wybrany poziom
 */
void MainWindow::on_horizontalSliderPoziom_sliderMoved(int position)
{
    ui->widget->changeLevel(float(position)/100);
}

/*!
 * \brief Otwiera okno wykresów
 */
void MainWindow::on_pushButtonWykresy_clicked()
{
    oknoWykresow.setModal(true);
    oknoWykresow.exec();
}

/*!
 * \brief Zmienia kolor cząsteczek
 *
 * Zmienia kolor cząsteczek zgodnie z wybranym z listy, wywołuje metodę zmiany koloru klasy GLWidget.
 * \param[in] color - indeks wybranego koloru
 */
void MainWindow::colorChanged(int color)
{
    ui->widget->changeColor(color);
}

/*!
 * \brief Zmienia szybkość poruszania się cząsteczek
 *
 * Zmienia szybkość poruszania się cząsteczek, wywołuje metodę zmiany szybkości klasy GLWidget.
 * \param[in] vel - wybrana szybkość
 */
void MainWindow::velocityChanged(double vel)
{
    ui->widget->changeVelocity(vel);
}
