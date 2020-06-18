#ifndef GLWIDGET_H
#define GLWIDGET_H

/*!
 * \file
 * \brief Plik opisujący sposób wizualizacji graficznej
 *
 * Plik zawiera deklaracje klas Particle oraz GLWidget
 */

#include <QObject>
#include <QGLWidget>
#include <QSurfaceFormat>
#include <QtOpenGL>
#include <QGLViewer/qglviewer.h>

/*!
 * \brief Deklaracja klasy Particle
 *
 * Klasa opisuje pojedynczą cząsteczkę wody, jej położenie, prędkość oraz kolor.
 */

class Particle {
public:
    /*!
     * \brief Wektor prędkości cząsteczki wzdłuż osi X, Y, Z
     */
    qglviewer::Vec speed;

    /*!
     * \brief Wektor położenia cząsteczki na osi X, Y, Z
     */
    qglviewer::Vec position;

    /*!
     * \brief Wektor przechowujący kolor RGB cząsteczki
     */
    QVector3D color = {0.0, 0.0, 1.0};

    /*!
     * \brief Położenie cząsteczki na osi Z przed wykonaniem przechylenia
     */
    float z_pocz;

    /*!
     * \brief Bezwzględne położenie cząsteczki na osi Z
     */
    float z0;

    /*!
     * \brief Konstruktor klasy Particle
     */
    Particle(float, float, float);

    /*!
     * \brief Inicjalizuje cząsteczkę w środowisku graficznym
     */
    void init();

    /*!
     * \brief Rysuje cząsteczkę
     */
    void draw();

    /*!
     * \brief Animuje cząsteczkę
     */
    void animate(float, float, float, bool, float);
};

/*!
 * \brief Deklaracja klasy GLWidget
 *
 * Klasa modeluje okno graficzne aplikacji, przechowuje aktualne wartości odchylenia, poziom oraz kolor płynu.
 */
class GLWidget : public QGLViewer
{
public:
    /*!
     * \brief Odchylenie szklanki względem osi X
     */
    int ax;

    /*!
     * \brief Odchylenie szklanki względem osi Y
     */
    int ay;

    /*!
     * \brief Znak wartości odchylenia względem osi X
     */
    float axp;

    /*!
     * \brief Znak wartości odchylenia względem osi Y
     */
    float ayp;

    /*!
     * \brief Konstruktor klasy GLWidget
     */
    GLWidget(QWidget *parent = 0);

    /*!
     * \brief Zmienia kolor cząsteczek
     */
    void changeColor(int);

    /*!
     * \brief Zmienia poziom płynu w szklance
     */
    void changeLevel(float);

    /*!
     * \brief Zmienia szybkość poruszania się cząsteczek
     */
    void changeVelocity(double);

private:
    /*!
     * \brief Inicjalizuje okno graficzne
     */
    void init();

    /*!
     * \brief Rysuje okno graficzne
     */
    void draw();

    /*!
     * \brief Animuje okno graficzne
     */
    void animate();

    /*!
     * \brief Liczba cząsteczek wody w szklance
     */
    int particleCount;

    /*!
     * \brief Aktualny poziom wody w szklance
     */
    float level = 1.00;

    /*!
     * \brief Promień podstawy szklanki
     */
    float radius = 0.5;

    /*!
     * \brief Tablica przechowująca wszystkie cząsteczki
     */
    Particle *particles[60800];

};

#endif // GLWIDGET_H
