#include <GLUT/glut.h>
#include <iostream>
#include <math.h>
#include "human.h"
#include "vehicle.h"
#include "building.h"
#include "industrial.h"

// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=0.0f, z=5.0f;

float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

GLint wallface[4] = { 0, 1, 2, 3 };

GLfloat wallVertices[][3] = {
    { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 },{ 1.0, 1.0, -1.0 },{ -1.0, 1.0, -1.0 }
 };

static GLuint textureWall;
static GLuint textureGround;
static GLuint textureLake;
static GLuint textureBuilding;


// Read the images
GLbyte wall[256][256][3];  //char* vs GLbyte
//char* bitmap;
GLbyte bitmap[256][256][3];

char* bitmap_lake;
char* bitmap_building;

//human *h = new human();
industrial i;
building b;
vehicle v;

/**
 * Fill the given matrix with a RAW image
 *
 * @param data The matrix to fill
 */
void readRAWImage(char* filename, GLbyte data[256][256][3]) {
  FILE * file;

  file = fopen(filename, "rb");
  if (file != NULL) {
    fread(data, 256 * 256 * 3, 1, file);
    fclose(file);
  }
}

/**
*  read tga files
*/
void readTGAImage(char* filename, char* bitmap) {

    long lSize;
    size_t result;
    FILE* fp = fopen(filename, "rb");
    fseek(fp, 0, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    bitmap = (char*) malloc(sizeof(char)*lSize);
    fread(bitmap, 1, lSize, fp);
    fclose(fp);
}

void readPNGImage(char* filename, char* bitmap){

    //TODO:
}


void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0) h = 1;

    float ratio =  w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 1.0f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void drawGround() {

    float latitude = 2.0;
    float longitude = 2.0;

    //glShadeModel(GL_FLAT);
    //glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1,1,1);

    //glTranslatef(0.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, textureGround);

    glBegin(GL_QUADS);

        glTexCoord2f(0.0, 0.0);  // Use bottom left texel
        glVertex3f(-latitude, 0.0f, -longitude);

        glTexCoord2f(0.0, 1.0);  // Use bottom right texel
        glVertex3f(-latitude, 0.0f,  longitude);

        glTexCoord2f(1.0, 1.0);  // Use top right texel
        glVertex3f( latitude, 0.0f,  longitude);

        glTexCoord2f(1.0, 0.0);  // Use top left texel
        glVertex3f( latitude, 0.0f, -longitude);

    glEnd();

/*
    // Create ground (8x)
    for (int f = 0; f < 4; f++) {

    glTranslatef(latitude*(-2), 0.0, 0.0);

    glPushMatrix();

    // Draw ground
    //glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_QUADS);

        glTexCoord2f(0.0, 0.0);  // Use bottom left texel
        glVertex3f(-latitude, 0.0f, -longitude);

        glTexCoord2f(0.0, 1.0);  // Use bottom right texel
        glVertex3f(-latitude, 0.0f,  longitude);

        glTexCoord2f(1.0, 1.0);  // Use top right texel
        glVertex3f( latitude, 0.0f,  longitude);

        glTexCoord2f(1.0, 0.0);  // Use top left texel
        glVertex3f( latitude, 0.0f, -longitude);

    glEnd();

    glPopMatrix();

    }


    glTranslatef(latitude*8, 0.0, longitude*(-2));

    // Create ground (8x)
    for (int f = 0; f < 4; f++) {

     glTranslatef(latitude*(-2), 0.0, 0.0);

    glPushMatrix();

    // Draw ground
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_QUADS);

        glTexCoord2f(0.0, 0.0);  // Use bottom left texel
        glVertex3f(-latitude, 0.0f, -longitude);

        glTexCoord2f(0.0, 1.0);  // Use bottom right texel
        glVertex3f(-latitude, 0.0f,  longitude);

        glTexCoord2f(1.0, 1.0);  // Use top right texel
        glVertex3f( latitude, 0.0f,  longitude);

        glTexCoord2f(1.0, 0.0);  // Use top left texel
        glVertex3f( latitude, 0.0f, -longitude);

    glEnd();

    glPopMatrix();

    }

    glTranslatef(latitude*8, 0.0, longitude*(-2));

        // Create wall (8x)
        for (int f = 0; f < 4; f++) {

         glTranslatef(latitude*(-2), 0.0, 0.0);

         glPushMatrix();

         // Draw ground
         glColor3f(0.8f, 0.8f, 0.0f);
         glBegin(GL_QUADS);

            glTexCoord2f(0.0, 0.0);  // Use bottom left texel
            glVertex3f(-latitude, 0.0f, -longitude);

            glTexCoord2f(0.0, 1.0);  // Use bottom right texel
            glVertex3f(-latitude, 0.0f,  longitude);

            glTexCoord2f(1.0, 1.0);  // Use top right texel
            glVertex3f( latitude, 0.0f,  longitude);

            glTexCoord2f(1.0, 0.0);  // Use top left texel
            glVertex3f( latitude, 0.0f, -longitude);

        glEnd();

        glPopMatrix();
        }

    glTranslatef(0.0, 0.0, 0.0);

    glFlush();

    */
}

void drawWall(){

    float step = - 1.0;
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1,1,1);
    glTranslatef(0.0, 1.0, -12.0);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, textureWall);

    // Create wall (8x)
    for (int f = 0; f < 16; f++) {

        glTranslatef(0.0, 2.0, 0.0);

        // Create the face
        glBegin(GL_QUADS);
        int v;

        v = wallface[0];
        glTexCoord2f(0.0, 0.0);  // Use bottom left texel
        glVertex3fv(wallVertices[v]);

        v = wallface[1];
        glTexCoord2f(0.0, 1.0);  // Use bottom right texel
        glVertex3fv(wallVertices[v]);

        v = wallface[2];
        glTexCoord2f(1.0, 1.0);  // Use top right texel
        glVertex3fv(wallVertices[v]);

        v = wallface[3];
        glTexCoord2f(1.0, 0.0);  // Use top left texel
        glVertex3fv(wallVertices[v]);

        glEnd();
    }

    glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);

    glTranslatef(0.0, 0.0, 0.0);
    // Force the rendering (off-screen)

    glFlush();
}



void drawBuildingFronside()
{
    float latitude = -10;
    float longitude = -10;
    //TODO:
}

/**
* draw lake
*/
void drawLake()
{
    float latitude = 10;
    float longitude = 10;
    float x = 10;

    //glClearColor();
    glTranslatef(longitude,1,latitude);
    glBindTexture(GL_TEXTURE_2D, textureLake);

    glBegin(GL_QUADS);

        //left corner
        glTexCoord2f(0,0);
        glVertex3f(-5,-5,x);

        //right corner
        glTexCoord2f(0,1);
        glVertex3f(5,-5,x);

        //right top corner
        glTexCoord2f(1,1);
        glVertex3f(5,5,x);

        //left top corner
        glTexCoord2f(1,0);
        glVertex3f(-5,5,x);

    glEnd();
    glTranslatef(0.0, 0.0, 0.0);

    glFlush();
}

void groundInitTexture()
{
    //glShadeModel(GL_FLAT);
    //glEnable(GL_DEPTH_TEST);

    //readRAWImage("images/sand.tga",xxx);
    readRAWImage("images/brick.raw", bitmap);

    //gen and bind texture
    glGenTextures(1, &textureGround); //??
    glBindTexture(GL_TEXTURE_2D, textureGround);

    // Set the parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

     // Create the texture object
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap); // images[0]);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap); // images[0]);
}

/**
*  wall texture
*/
void wallInitTexture()
{
    //glShadeModel(GL_FLAT);
    //glEnable(GL_DEPTH_TEST);
    readRAWImage("images/brick.raw", wall);

    //bind texture
    glGenTextures(1, &textureWall);
    glBindTexture(GL_TEXTURE_2D, textureWall);

    // Set the parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Create the texture object
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, wall);
}

/**
 WTF black texture
* lake texture
*/
void lakeInitTexture()
{
    readTGAImage("images/industrial_building2.tga", bitmap_lake);

    glGenTextures(1, &textureLake);
    glBindTexture(GL_TEXTURE_2D, textureLake);

    // Set the parameters
    /*glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    */

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 979, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap_lake);
}

void buildingInitTexture()
{
   readTGAImage("images/industrial_building.tga",bitmap_building);

   glGenTextures(1, &textureBuilding);
   glBindTexture(GL_TEXTURE_2D, textureBuilding);

   glTexImage2D(GL_TEXTURE_2D, 0,3, 1024, 1024, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap_building);
}

void drawOrientationPoint()
{
    glTranslatef(0,-2,0);

    glBegin(GL_LINES);

        glVertex3f(0,-5,0);
        glVertex3f(0,10,0);

        GLfloat x = 1;
        GLfloat y = 0;
        float len = 0;

        int ang = 0;
        int rad = 0;

        GLfloat test = cos(90);


        for (int k=0; k<6; k++) {

            //glRotatef(30,0,1,0);

            //2PI RAD = 360;
            //PI RAD = 180



            x = cos(ang);
            y = sin(ang);

            glVertex3f(0, 0, 0);
            glVertex3f(x, 0, y);

            ang += 45;
            len += 4;
        }
    glEnd();
}

void renderScene(void){

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;

    glLoadIdentity();
    // Set the camera
    gluLookAt(x, 1.0f, z, x+lx, 1.0f,  z+lz, 0.0f, 1.0f,  0.0f);

    //glTranslatef(0.0f, -0.5f, 0.0f);

    //bindTextureTorus();
/*
    h.drawHead();
    h.drawArms();
    h.drawBody();
    //h->drawHead();

    b.drawBuilding();
    b.drawBuilding2();
*/

    glTranslatef(0.0, 0.0, 0.0);

    //glShadeModel(GL_FLAT);
    //glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
        drawGround();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
        drawWall();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
        drawLake();
    glDisable(GL_TEXTURE_2D);

    //i.drawIndustrial();

   // glTranslatef(0.0f, -1.8f, 0.0f);
    //glTranslatef(0.0, -6.0,0.0); //WTF? each component must start an y=0

    if (v.getSpeed() > 0) {
        v.moveForward();
    }
    v.drawVehicle();

    drawOrientationPoint();

    glutSwapBuffers();
}

void pressKey(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_UP : deltaMove = 1.8f; break;
        case GLUT_KEY_DOWN : deltaMove = -1.8f; break;
        case GLUT_KEY_LEFT :
            angle -= 0.1f;
            lx = sin(angle);
            lz = -cos(angle);
        break;
        case GLUT_KEY_RIGHT:
            angle += 0.1f;
            lx = sin(angle);
            lz = -cos(angle);
        break;
    }
}

void vehicleKey(unsigned char key, int x, int y)
{
    switch(key) {
         case 'a':
            v.accelerate();
            break;
        case 's':
            v.braking();
            break;
        case 'y':
            v.turnLeft();
            break;
        case 'x':
            v.turnRight();
            break;
    }
}


void releaseKey(int key, int x, int y)
{
    switch(key) {
       case GLUT_KEY_UP :
       case GLUT_KEY_DOWN : deltaMove=0; break;
       case GLUT_KEY_LEFT :
       case GLUT_KEY_RIGHT: deltaAngle =0; break;
    }
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(1220,720);
    glutCreateWindow("Game Shooter #1");

    groundInitTexture();
    wallInitTexture();
    lakeInitTexture();
    //buildingInitTexture();

    //vehicle
    v.addTexture();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    glutKeyboardFunc(vehicleKey);

    glutMainLoop();
    return 1;
}