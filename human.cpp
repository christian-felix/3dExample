#include "human.h"
#include <GLUT/glut.h>

human::human()
{
    position_x = 0.0;
    position_y = 0.0;
    position_z = 0.0;
}

void human::drawHead()
{
    glPushMatrix();
        glTranslatef(position_x - 4.5, position_y + 0.5, position_z -2.0);
        glColor3f(1.4f, 2.4f, 0.4f);
        glutWireSphere(0.4, 20, 16);
    glPopMatrix();
}
void human::drawArms()
{
    /*glPushMatrix();

        glColor3f(1.1f, 1.1f, 0.4f);
        glTranslated(3.5,1.5,-2);
        glRotated(0.0, 0.0, 1.0, 0.0);
        glutWireCube(2);

        GLUquadricObj *quadratic;
        quadratic = gluNewQuadric();
        glRotatef(45.0f, 0.0f, 1.0f, -0.5f);
        glColor3f(0.4f, 0.4f, 0.4f);
        gluCylinder(quadratic,0.1f,0.1f,3.0f,32,32);

    glPopMatrix();*/
}

void human::drawBody()
{

}

void human::drawLegs()
{
    glPushMatrix();

    glPopMatrix();
}