#include "vehicle.h"
#include <GLUT/glut.h>
#include <iostream>
#include <math.h>

vehicle::vehicle()
{
    speed = 0;
    angle = 0.0;
    direction = 0.0;
    position_x = 0.0;
    position_y = 0.0;
    position_z = 0.0;
}

void vehicle::addTexture()
{
    readImage("images/tire.tga", image);
}

void vehicle::drawVehicle()
{
    //drawSeats();



    glMatrixMode(GL_MODELVIEW);

    glTranslatef(0.0 + position_x, 0.0 , 0.0 - position_z);
    glRotatef(direction, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0 - position_x, 0.0, 0.0 - position_z);

    drawDoors();
    drawTires();
}

void vehicle::drawTires()
{
    float axe = -0.5;

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    glBindTexture(GL_TEXTURE_2D, texture);

    //front tires
    for(int i=0; i<2; i++) {

        glPushMatrix();
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslatef(position_x, position_y + 1, position_z - axe);
            glRotatef(angle, 0.0f, 1.0f, 0.0f);
            glRotatef(speed, 1.0f, 0.0f, 0.0f);
            glutSolidTorus(0.1, 0.2, 20, 30);
        glPopMatrix();
        axe -= 1;
    }

    axe = -0.5;

    for(int i=0; i<2; i++) {
        glPushMatrix();
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslatef(position_x + 1.0, position_y + 1, position_z - axe);
            glRotatef(speed, 1.0f, 0.0f, 0.0f);
            glutSolidTorus(0.1, 0.2, 20, 30);
        glPopMatrix();
        axe -= 1;
    }

    glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);

    axe = -0.5;

    glPushMatrix();
        glTranslatef(position_x, position_y + 1.0, position_z - axe);
        glColor3f(0.4f, 0.4f, 0.4f);
        gluCylinder(quadratic, 0.03f, 0.03f, 1.0f, 32, 32);
    glPopMatrix();

    axe = -0.5;

    glPushMatrix();
        glTranslatef(position_x + 1.0, position_y + 1.0, position_z - axe);
        glColor3f(0.4f, 0.4f, 0.4f);
        gluCylinder(quadratic, 0.03f, 0.03f, 1.0f, 32, 32);
    glPopMatrix();
}

void vehicle::drawDoors()
{
    float axe = -0.5;

    //doors
    glPushMatrix();
         glColor3f(0.4f, 0.0f, 0.6f);
        glTranslatef(position_x, position_y +1.2 , position_z - axe);
        glBegin(GL_POLYGON);
            glVertex2f(0.2, -0.3);
            glVertex2f(0.8, -0.3);
            glVertex2f(1.0, 0.2);
            glVertex2f(0.0, 0.0);
        glEnd();
   glPopMatrix();

    axe += 2.0;

   glPushMatrix();
        glTranslatef(position_x, position_y + 1.2 , position_z + axe);
        glBegin(GL_POLYGON);
            glVertex2f(0.2 , -0.3);
            glVertex2f(0.8, -0.3);
            glVertex2f(1.0, 0.2);
            glVertex2f(0.0, 0.0);
        glEnd();
   glPopMatrix();

   axe = 0.5;

   glPushMatrix();
        glTranslatef(position_x + 0.5, position_y + 1.1, position_z + axe + 0.5);
        glColor3f(1.1f, 1.1f, 0.4f);
        glScalef(1,0.5,1);
        glutWireCube(0.8);
   glPopMatrix();

}


void vehicle::drawSeats()
{
   float axe = -0.5;

   glTranslatef(position_x - 1.0, position_y + 1.0, position_z);

    glPushMatrix();
        glColor3f(0.2f, 0.2f, 0.5f);
        glBegin(GL_POLYGON);
            glVertex2f(4, 1);
            glVertex2f(4.4, 1);
            glVertex2f(4.4, 1.2);
            glVertex2f(4, 1.2);
        glEnd();
    glPopMatrix();

    glTranslatef(position_x, position_y + 1.0, position_z - axe);

   glPushMatrix();
        glColor3f(0.1f, 0.2f, 0.3f);
        glBegin(GL_POLYGON);
            glVertex2f(2, 1);
            glVertex2f(2.2, 1);
            glVertex2f(2.2, 1.2);
            glVertex2f(2, 1.2);
        glEnd();
    glPopMatrix();
}

void vehicle::moveForward()
{
   GLfloat radiant = (GLfloat) (direction * 0.017453292519943) * (-1);

    float x = sin(radiant) * 0.1;
    float z = cos(radiant) * 0.1;

    position_x -= z * speed;
    position_z += x * speed;

    if (angle > 0 ) {
        angle -= 3;
    } else if (angle < 0 ) {
        angle += 3;
    }
}

void vehicle::moveBackward()
{
    position_x -= 0.1;
}

void vehicle::accelerate()
{
    speed += 0.5;

    if (speed > 10) speed = 10;
}

void vehicle::braking()
{
    speed -= 0.4;
    if (speed < 0) speed= 0;
}

float vehicle::getSpeed()
{
    return speed;
}

void vehicle::turnLeft()
{
    angle += 10.0;
    if (angle > 45) angle = 45;

    if (speed > 0) {
        direction += 5;
        if (direction > 360) direction = 0;
    }

}

void vehicle::turnRight()
{
    angle -= 10.0;
    if(angle < -45) angle = -45;

    if (speed > 0) {
        direction -= 5;
        if (direction < -360) direction = 0;
    }
}


void vehicle::readImage(char* filename, GLbyte data[256][256][3]) {
  FILE * file;

  file = fopen(filename, "rb");
  if (file != NULL) {
    fread(data, 256 * 256 * 3, 1, file);
    fclose(file);
  } else {

  }
}

