#include "tab_zakladka.h"
#include "tab_zakladka.h"
#include "ui_tab_zakladka.h"
#include "QString"
#include "QtDebug"
#include "tab_zakladka.h"

/*!
 * \file
 * \brief Deklaracja klasy tab_zakladka
 */

/*!
 * \brief Konstruktor klasy
 *
 * Tworzy obiekt tab_zakladka, wypełnia listę dostępnych kolorów
 * \param[in] parent - rodzic obiektu
 */
tab_zakladka::tab_zakladka(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tab_zakladka)
{
    ui->setupUi(this);
    ui->comboBoxKolor->addItem("niebieski");
    ui->comboBoxKolor->addItem("czerwony");
    ui->comboBoxKolor->addItem("różowy");
    ui->comboBoxKolor->addItem("zielony");
    ui->comboBoxKolor->setCurrentIndex(0);
}

/*!
 * \brief Destruktor klasy
 */
tab_zakladka::~tab_zakladka()
{
    delete ui;
}

/*!
 * \brief Aktualizuje zmianę wartości szybkości slidera
 *
 * Wysyła sygnał zmiany wartości szybkości, aktualizuje wartość w spinBoxSzybkosc
 * \param[in] value - nowa wartość szybkości
 */
void tab_zakladka::on_horizontalSliderSzybkosc_valueChanged(int value)
{
    double val = (double)(ui->horizontalSliderSzybkosc->value())/100;
    ui->doubleSpinBoxSzybkosc->setValue(val);
    sigVelocity((double)value/100);
}

/*!
 * \brief Aktualizuje zmianę wartości szybkości comboBoxa
 *
 * Aktualizuje zmianę wartości szybkości w horizontalSliderSzybkosc.
 * \param[in] arg1 - nowa wartość szybkości
 */
void tab_zakladka::on_doubleSpinBoxSzybkosc_valueChanged(double arg1)
{
    ui->horizontalSliderSzybkosc->setValue(arg1*100);
}

/*!
 * \brief Zmienia kolor cząsteczek
 *
 * Wysyła sygnał zmiany koloru
 * \param[in] index - indeks wybranego koloru
 */
void tab_zakladka::on_comboBoxKolor_currentIndexChanged(int index)
{
    sigColor(index);
}


