#ifndef WYKRESWINDOW_H
#define WYKRESWINDOW_H

#include <QDialog>
#include <QtCharts>

/*!
 * \file
 * \brief Deklaracja klasy WykresWindow
 *
 * Klasa odpowiada za wyświetlanie wykresu wartości odchyleń w czasie
 */
namespace Ui {
class WykresWindow;
}

class WykresWindow : public QDialog
{
    Q_OBJECT

public:

    /*!
     * \brief Konstruktor klasy WykresWindow
     */
    WykresWindow(QWidget *parent = nullptr);

    /*!
     * \brief Destruktor klasy WykresWindow
     */
    ~WykresWindow();

    /*!
     * \brief Dodaje nowe wartości do serii pomiarów
     */
    void addValues(int, int);

private slots:
    /*!
     * \brief Zamyka okno
     */
    void on_pushButtonZamknij_clicked();

    /*!
     * \brief Czyści wykres
     */
    void on_pushButtonWyczysc_clicked();

private:
    Ui::WykresWindow *ui;
    /*!
     * \brief Seria pomiarów odchylenia względem osi X
     */
    QLineSeries *seriesX;

    /*!
     * \brief Seria pomiarów odchylenia względem osi Y
     */
    QLineSeries *seriesY;

    /*!
     * \brief Wykres
     */
    QChart *chart;

    /*!
     * \brief Okno wyświetlające wykres
     */
    QChartView *chartView;

    /*!
     * \brief Oś pozioma
     */
    QValueAxis *xAxis;

    /*!
     * \brief Oś pionowa
     */
    QValueAxis *yAxis;

    /*!
     * \brief zmienna przechowująca kolejne kroki osi poziomej
     */
    int i = 0;
};

#endif // WYKRESWINDOW_H
