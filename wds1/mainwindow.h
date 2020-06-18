#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include "crc.h"
#include "wykreswindow.h"
#include "tab_zakladka.h"
#include "glwidget.h"


/*!
 * \file
 * \brief Deklaracja klasy MainWindow
 *
 * W klasie znajdują się wszystkie elementy występujące w oknie aplikacji oraz obsługa połączenia z mikrokontrolerem
 */
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor klasy MainWindow
     */
    MainWindow(QWidget *parent = nullptr);

    /*!
     * \brief Destruktor klasy MainWindow
     */
    ~MainWindow();

private slots:
    /*!
     * \brief Odczytuje dane z portu szeregowego
     */
    void readFromPort();

    /*!
     * \brief Wykonuje akcje po wciśnięciu przycisku "Szukaj"
     */
    void on_pushButtonSearch_clicked();

    /*!
     * \brief Dodaje tekst do okna logów
     */
    void addToLogs(QString message);

    /*!
     * \brief Wykonuje akcje po wciśnięciu przycisku "Połącz"
     */
    void on_pushButtonConnect_clicked();

    /*!
     * \brief Wykonuje akcje po wciśnięciu przycisku "Rozłącz"
     */
    void on_pushButtonDisconnect_clicked();

    /*!
     * \brief Wykonuje akcje po zmianie wartości slidera "Poziom"
     */
    void on_horizontalSliderPoziom_sliderMoved(int position);

    /*!
     * \brief Wykonuje akcje po wciśnięciu przycisku "Wykres"
     */
    void on_pushButtonWykresy_clicked();

    /*!
     * \brief Wykonuje akcje po wciśnięciu przycisku "Zamknij"
     */
    void on_pushButtonClose_clicked();

public slots:

    /*!
     * \brief Zmienia kolor cząsteczek
     */
    void colorChanged(int);

    /*!
     * \brief Zmienia szybkość cząsteczek
     */
    void velocityChanged(double);
private:
    /*!
     * \brief Grafika klasy MainWindow
     */
    Ui::MainWindow *ui;

    /*!
     * \brief Wartość odchylenia wzlędem osi X
     */
    int roll;

    /*!
     * \brief Wartość odchylenia względem osi Y
     */

    int pitch;
    /*!
     * \brief Port szeregowy połączonego urządzenia
     */
    QSerialPort *device;

    /*!
     * \brief Okno z wykresem
     */
    WykresWindow oknoWykresow;
};
#endif // MAINWINDOW_H
