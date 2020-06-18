#include "glwidget.h"
#include <QDebug>
#include <GL/glu.h>
#include <GL/gl.h>
#include <cmath>

/*!
 * \file
 * \brief Plik zawierający deklaracje klas GLWidget i Particle
 */

/*!
 * \brief Konstruktor klasy GLWidget
 * \param[in] parent - rodzic widgetu
 */
GLWidget::GLWidget(QWidget *parent):QGLViewer(parent)
{

}

/*!
 * \brief Rysuje okno graficzne
 *
 * Rysuje okno graficzne oraz scenę i jej zawartość.
 */
void GLWidget::draw() {
    drawAxis(10);
    glColor4f(0.1,0.1,0.1,0.1);
    glBegin(GL_QUADS);
        glVertex3f(-10.0f, 10.0f, 0.0f);
        glVertex3f(10.0f, 10.0f, 0.0f);
        glVertex3f(10.0f, -10.0f, 0.0f);
        glVertex3f(-10.0f, -10.0f, 0.0f);
    glEnd();
    if(ax!=0 || ay!=0){
        float temp1=sqrt((float)(pow(ay,2))/(float)(pow(ax,2)+pow(ay,2)));
        float temp2=sqrt((float)(pow(ax,2))/(float)(pow(ay,2)+pow(ax,2)));

        glTranslatef(temp1*axp*0.5, temp2*ayp*0.5,0.0);
        glRotatef(ax,1,0,0);
        glRotatef(ay,0,1,0);
        glTranslatef(-temp1*axp*0.5,-temp2*ayp*0.5,0.0);
    }
        glColor4f(0.1,0.1,0.1,0.1);
        int slices = 36;
        for(int i=0; i<slices; i++) {
          float theta = ((i*360/slices))*3.1415/180;
          float nextTheta = ((i+1)*360/slices)*3.1415/180;
          glBegin(GL_TRIANGLE_STRIP);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(radius*sin(theta), radius*cos(theta), 0);
            glVertex3f (radius*sin(nextTheta), radius*cos(nextTheta),0);
          glEnd();
          glBegin(GL_POLYGON);
            glVertex3f(radius*sin(theta), radius*cos(theta), 0);
            glVertex3f (radius*sin(nextTheta), radius*cos(nextTheta),0);
            glVertex3f (radius*sin(nextTheta), radius*cos(nextTheta),2.0);
            glVertex3f(radius*sin(theta), radius*cos(theta), 2.0);
          glEnd();
        }
        glBegin(GL_POINTS);
        for (int i = 0; i < particleCount; i++)
          {
            particles[i]->draw();
        }
        glEnd();
//        drawAxis(3);

}

/*!
 * \brief Inicjalizuje okno graficzne
 *
 * Inicjalizuje okno graficzne, źródło światła, kolor tła, położenie kamery.
 * Tworzy obiekty klasy Particle oraz przypisuje je do tablicy particles.
 */
void GLWidget::init() {
  restoreStateFromFile();
  glClearColor(0.97,0.81,0.81,1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable (GL_DEPTH_TEST ) ;
  this->camera()->setOrientation(0,-90);
  this->camera()->setPosition({0.0,10.0,0.0});
  this->camera()->lookAt({0.0,0.0,0.0});
  float tempY;
  int count=0;
  for (float i=0.5; i>0; i-=0.05)
  {
     for (float j=0.5; j>0;j-=0.025)
     {
         for(float k=0;k<level;k+=0.02)
         {
            tempY = sqrt(pow(i,2)-pow(j,2));
            particles[count++]=new Particle(j,tempY, k);
            particles[count++]=new Particle(j,-tempY, k);
            particles[count++]=new Particle(-j,tempY,k);
            particles[count++]=new Particle(-j,-tempY,k);
         }
     }
  }
  particleCount=count-1;
  glPointSize(7.0);
  startAnimation();
}

/*!
 * \brief Animuje okno graficzne
 *
 * Wywołuje metodę animate klasy Particle dla wszystkich obiektów znajdujących się w tablicy particles.
 */
void GLWidget::animate() {
    float tan_gamma;
    float temp2, temp1;
    float wspolczynnik;
    bool isNad;
    tan_gamma=acos(cos(ax*3.1415/180)*cos(ay*3.1415/180));
    tan_gamma = tan(tan_gamma);
    temp1=sqrt((float)(pow(ay,2))/(float)(pow(ax,2)+pow(ay,2)));
    temp2=sqrt((float)(pow(ax,2))/(float)(pow(ay,2)+pow(ax,2)));
    temp1=temp1*(axp)*0.5;
    temp2=temp2*(ayp)*0.5;
    wspolczynnik= temp2/temp1;
    if(temp2>temp1*-1/wspolczynnik)
        isNad = true;
    else
        isNad = false;
  for (int i = 0; i < particleCount; i++)
  {
    particles[i]->animate(radius, tan_gamma, -1/wspolczynnik, isNad, level);
  }
}

/*!
 * \brief Konstruktor klasy Particle
 *
 * Tworzy obiekt Particle, przypisuje mu położenia zadane w argumentach.
 * Przypisuje wartości z_pocz i z0.
 * \param[in] x - pozycja obiektu na osi X
 * \param[in] y - pozycja obiektu na osi Y
 * \param[in] z - pozycja obiektu na osi Z
 */
Particle::Particle(float x, float y, float z)
{
    init();
    position.x=x;
    position.y=y;
    position.z=z;
    z_pocz = position.z;
    z0 = position.z;
}

/*!
 * \brief Animuje obiekt Particle
 *
 * Wyznacza na jakiej wysokości będzie się znajdował obiekt w zależności od położenia na osiach X,Y oraz nachylenia
 * \param[in] rad - promień podstawy szklanki
 * \param[in] tan_gamma - tangens kąta nachylenia szklanki
 * \param[in] wspolczynnik - wspolczynnik prostej, względem której następuje zwiększanie lub zmniejszanie położenia
 * \param[in] isNad - określa, czy punkt osi obrotu znajduje się nad prostą czy pod
 * \param[in] level - aktualny poziom wody w szklance
 */
void Particle::animate(float rad, float tan_gamma, float cos, bool isNad, float level) {
    float d;
    float h;
    h=rad*tan_gamma;
    h=sqrt(pow(h,2));
    d = sqrt(pow(cos*position.x-position.y,2))/sqrt(pow(cos,2)+1);
    h = d*h/rad;
    if (isNad && position.y-position.x*cos>0 ){
        if(position.z < z0*(level+h)/level){
             position.z += 0.01f*speed.z;
          }
        if(position.z > z0*(level+h)/level){
             position.z -= 0.01f*speed.z;
          }
        }
    else if (!isNad && position.y-position.x*cos<=0 ) {
        if(position.z < z0*(level+h)/level){
           position.z += 0.01f*speed.z;
          }
        if(position.z > z0*(level+h)/level){
             position.z -= 0.01f*speed.z;
          }
        }
    else{
        if(position.z > z0*(level-h)/level){
        position.z -= 0.01f*speed.z;
        }
        if(position.z < z0*(level-h)/level){
        position.z += 0.01f*speed.z;
        }
    }
      if(position.z < 0)
         position.z = 0;
      if(position.z > 2)
         position.z = 0;
}

/*!
 * \brief Rysuje obiekt Particle
 *
 * Wyświetla obiekt Particle w oknie graficznym, przypisuje kolor
 */
void Particle::draw() {
    if (position.z>2)
        glColor4f(0.0, 0.0, 0.0,0.0);
    else
        glColor4f(color.x(), color.y(), color.z(), 0.2);
    glVertex3fv(position);
}

/*!
 * \brief Inicjalizuje obiekt Particle
 *
 * Przypisuje wartość początkową prędkości cząsteczki.
 */
void Particle::init() {
  speed=qglviewer::Vec(0,0,1.0);
}

/*!
 * \brief Zmienia kolor cząsteczek
 *
 * Zmienia kolor cząsteczek w zależności od aktualnie wybranego
 * \param[in] color - indeks koloru w liście
 */
void GLWidget::changeColor(int color)
{
    switch(color){
    case 0:
        for(int i = 0; i<particleCount; i++)
            particles[i]->color={0.0, 0.0, 1.0};
        break;
    case 1:
        for(int i = 0; i<particleCount; i++)
            particles[i]->color={1.0, 0.0, 0.0};
        break;
    case 2:
        for(int i = 0; i<particleCount; i++)
            particles[i]->color={1.0, 0.0, 1.0};
        break;
    case 3:
        for(int i = 0; i<particleCount; i++)
            particles[i]->color={0.0, 1.0, 0.0};
        break;
    }
}

/*!
 * \brief Zmienia poziom wody w szklance
 * \param[in] lvl - nowy poziom wody
 */
void GLWidget::changeLevel(float lvl)
{
    level = lvl;
    for (int i = 0; i<particleCount; i++){
        particles[i]->z0 = particles[i]->z_pocz*level;
        particles[i]->position.z = particles[i]->z_pocz*level;
    }
}

/*!
 * \brief Zmienia szybkość poruszania się cząsteczek w tablicy particles
 * \param[in] vel - nowa szybkość
 */
void GLWidget::changeVelocity(double vel)
{
    for(int i = 0; i<particleCount; i++)
    {
        particles[i]->speed.z = vel;
    }
}
