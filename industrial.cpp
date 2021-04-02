#include "industrial.h"
#include <GLUT/glut.h>
#include <iostream>
#import <stdlib.h>
#import <stdio.h>
#import <assert.h>



industrial::industrial()
{
    width = 1024;
    height = 789;
    depth = 20;

    position_x = -3.0;
    position_y = 6.5;
    position_z = 0.0;

    front_bitmap = readTgaImage("images/industrial_building.tga", front_bitmap);
    right_bitmap = readTgaImage("images/industrial_building2.tga", right_bitmap);
}

void industrial::drawIndustrial()
{

    glEnable(GL_TEXTURE_2D);

    drawIndustrialFront();
    drawIndustrialSide();

    glDisable(GL_TEXTURE_2D);
}

void industrial::drawIndustrialFront()
{
    glTranslatef(position_x, position_y ,  position_z);

    glGenTextures(1, &front_texture);
    glBindTexture(GL_TEXTURE_2D, front_texture);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, front_bitmap);

    glBindTexture(GL_TEXTURE_2D, front_texture);
    glColor3ub(255, 255, 255);

    glPushMatrix();

        glRotatef(90.0, 0,0,1);

        glBegin(GL_QUADS);

            glTexCoord2f(0,0);
            glVertex3f(-10, 0 , 1); //left bottom

            glTexCoord2f(0, 1);
            glVertex3f(10, 0, 1);  //right bottom

            glTexCoord2f(1, 1);
            glVertex3f(10, 20, 1);  //right top

            glTexCoord2f(1, 0);
            glVertex3f(-10, 20, 1);  //letf top

        glEnd();

    glPopMatrix();


   // glTranslatef(0.0, 0.0, 0.0); //reset position
}

void industrial::drawIndustrialSide()
{
    glTranslatef(position_x+15, position_y - 15 ,  position_z);

    //glRotatef(180,0,1,0);

    glGenTextures(1, &front_texture);

    glBindTexture(GL_TEXTURE_2D, right_texture);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, right_bitmap);

    glBindTexture(GL_TEXTURE_2D, right_texture);
    glColor3ub(255, 255, 255);

    glPushMatrix();

        glRotatef(90.0, 0,1,0);

        glBegin(GL_QUADS);

            glTexCoord2f(0,0);
            glVertex3f(-10, 0 , 1); //left bottom

            glTexCoord2f(0, 1);
            glVertex3f(10, 0, 1);  //right bottom

            glTexCoord2f(1, 1);
            glVertex3f(10, 20, 1);  //right top

            glTexCoord2f(1, 0);
            glVertex3f(-10, 20, 1);  //letf top

        glEnd();

    glPopMatrix();

    glTranslatef(0.0,0.0,0.0);
}

/**
*  read tga files
*/
char* industrial::readTgaImage(char* filename, char* bitmap) {

    long lSize;
    size_t result;
    FILE* fp = fopen(filename, "rb");
    fseek(fp, 0, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    bitmap = (char*) malloc(sizeof(char)*lSize);
    fread(bitmap, 1, lSize, fp);
    fclose(fp);

   return bitmap;
}
