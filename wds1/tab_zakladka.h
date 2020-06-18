 #ifndef TAB_ZAKLADKA_H
#define TAB_ZAKLADKA_H

#include <QWidget>

/*!
 * \file
 * \brief Definicja klasy tab_zakladka zawierająca parametry cieczy
 *
 * Zawiera aktualne parametry cieczy - szybkość poruszania się cząsteczek oraz ich kolor.
 */

namespace Ui {
class tab_zakladka;
}

class tab_zakladka : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor klasy tab_zakladka
     */
    tab_zakladka(QWidget *parent = nullptr);

    /*!
     * \brief Destruktor klasy tab_zakladka
     */
    ~tab_zakladka();

private slots:
    /*!
     * \brief Aktualizuje zmianę wartości szybkości sliderem
     */
    void on_horizontalSliderSzybkosc_valueChanged(int);

    /*!
     * \brief Aktualizuje zmianę wartości szybkości comboBoxem
     */
    void on_doubleSpinBoxSzybkosc_valueChanged(double);

    /*!
     * \brief Zmienia kolor cząsteczek
     */
    void on_comboBoxKolor_currentIndexChanged(int);

public:
    Ui::tab_zakladka *ui;
signals:
    /*!
     * \brief Sygnał przesyłający aktualnie wybrany kolor
     */
    void sigColor(int);

    /*!
     * \brief Sygnał przesyłający aktualną szybkość
     */
    void sigVelocity(double);
};

#endif // TAB_ZAKLADKA_H
