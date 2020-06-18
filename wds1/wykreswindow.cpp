#include "wykreswindow.h"
#include "ui_wykreswindow.h"
/*!
 * \file
 * \brief Definicja klasy WykresWindow
 */


/*!
 * \brief Konstruktor klasy WykresWindow
 *
 * Określa właściwości osi wykresów, tworzy serie pomiarów.
 * \param[in] parent - rodzic obiektu
 */
WykresWindow::WykresWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WykresWindow)
{
    ui->setupUi(this);
    chart = new QChart();
    seriesX = new QSplineSeries();
    seriesY = new QSplineSeries();
    yAxis = new QValueAxis();
    xAxis = new QValueAxis();
    yAxis->setTitleText("stopnie");
    chart->addSeries(seriesX);
    chart->addSeries(seriesY);
    yAxis->setRange(-90,90);
    xAxis->setRange(0,1000);
    seriesX->setName("X");
    seriesY->setName("Y");
    chartView = new QChartView(chart);
    chartView->chart()->setAxisY(yAxis,seriesX);
    chartView->chart()->setAxisX(xAxis,seriesX);
    chartView->chart()->setAxisY(yAxis,seriesY);
    chartView->chart()->setAxisX(xAxis,seriesY);
    ui->verticalLayout->addWidget(chartView);
    chartView->setRenderHint(QPainter::Antialiasing);
}

/*!
 * \brief Destruktor klasy WykresWindow
 */
WykresWindow::~WykresWindow()
{
    delete ui;
}

/*!
 * \brief Dodaje wartości do serii pomiarów
 *
 * Dodaje wartości do serii X, Y, aktualizuje wartości osi poziomej zgodnie z upływem czasu
 * \param[in] ax - kąt odchylenia względem osi X
 * \param[in] ay - kąt odchylenia względem osi Y
 */
void WykresWindow::addValues(int ax, int ay)
{
    chart->axisX()->setRange((float)(i+1)/10 - 10,(float)(i+1)/10);
    seriesX->append((float)i/10, ax);
    seriesY->append((float)i/10, ay);
    i++;
}

/*!
 * \brief Zamyka okno
 */
void WykresWindow::on_pushButtonZamknij_clicked()
{
    this->close();
}

/*!
 * \brief Czyści wykres
 *
 * Metoda usuwa wszystkie wartości z serii X i Y oraz resetuje czas.
 */
void WykresWindow::on_pushButtonWyczysc_clicked()
{
    seriesX->clear();
    seriesY->clear();
    i=0;
}
