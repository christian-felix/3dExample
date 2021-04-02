#include <GLUT/glut.h>
#include <iostream>
#import <stdlib.h>
#import <stdio.h>
#import <assert.h>


GLuint width=1024, height=789;
GLuint texture;
const char* const filename= "images/industrial_building.tga";

void init()
{
    // Initialization

    int size = 512;
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 1000, 1000);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, width/(float)height, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, -50, 0, 0, 0, 0, 1, 0);

    // Texture
   /* char bitmap[size][size][3];
    FILE* fp=fopen(filename, "r");
    assert(fp);
    assert(fread(bitmap, 3*sizeof(char), size*size, fp) == size*size);
    fclose(fp);
*/

    long lSize;
    char* bitmap;
    size_t result;
    FILE* fp = fopen(filename, "rb");
    fseek(fp, 0, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    bitmap = (char*) malloc(sizeof(char)*lSize);
    fread(bitmap, 1, lSize, fp);
    fclose(fp);


    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 789, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap);


    //free(bitmap); //error

  //  glGenerateMipmap(GL_TEXTURE_2D);
}

void display()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3ub(255, 255, 255);

   glBegin(GL_QUADS);

               glVertex3f(-10, -10 , 0);    //bottom left
               glTexCoord2f(0,0);

               glVertex3f(-10, 10, 0);     //top left
               glTexCoord2f(0, 1);

               glVertex3f(10, 10, 0);    //top right
               glTexCoord2f(1, 1);

               glVertex3f(10, -10, 0);    //bottom right
               glTexCoord2f(1, 0);


           glEnd();

    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}


int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}