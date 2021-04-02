#include "building.h"
#include <GLUT/glut.h>
#include <iostream>


building::building()
{
    position_x = -8.0;
    position_y = 1.5;
    position_z = -3.0;

    readImage("images/brick.raw", image);
    int* size = readImageTGA("images/industrial_building.tga", imageData);

    w = size[0];
    h = size[1];

  //  std::cout<<" w: "<<w<<" h:"<<h<<" ";
    //front[] = {0,1,2,3};
    //vertices[][3] = {{ -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 },{ 1.0, 1.0,-1.0 },{ 1.0, 1.0, -1.0 }};
}

void building::drawBuilding()
{
    //readImage("images/industrial_building.jpg", image);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glEnable(GL_TEXTURE_GEN_T);

        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

     /*   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        */
        glBindTexture(GL_TEXTURE_2D, texture);

    /*    glPushMatrix();
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslatef(position_x, position_y, position_z);
            glutSolidCube(6);
        glPopMatrix();
        */

        // Create the face

GLint wallface[4] = { 0, 1, 2, 3 };

GLfloat wallVertices[][3] = {
    { -2.0, -1.0, -1.0 }, { 2.0, -1.0, -1.0 },{ 2.0, 1.0, -1.0 },{ -2.0, 1.0, -1.0 }
    };

        glPushMatrix();


            glTranslatef(position_x, position_y, position_z);

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

        glPopMatrix();

        glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);


    glPushMatrix();
            glColor3f(0.3f, 0.3f, 0.4f);
            glTranslated(position_x, position_y + 1.0, position_z);
            glRotated(-90.0, 45.0, 1.0, 0.0);
            glutSolidCone(1, 2, 20, 20);
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
}


void building::drawBuilding2()
{
        glEnable(GL_TEXTURE_2D);
        /*glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        glEnable(GL_TEXTURE_GEN_T);
*/
      //  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	    //free(imageData);

        /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        */
        glBindTexture(GL_TEXTURE_2D, texture2);

        /*
         glPushMatrix();
            glColor3f(1.0f, 1.0f, 1.0f);
            glTranslatef(position_x+13, position_y, position_z);
            glutSolidCube(8);
        glPopMatrix();
        */


        // Create the face

GLint wallface[4] = { 0, 1, 2, 3 };

GLfloat wallVertices[][3] = {
    { -2.0, -1.0, -1.0 }, { 2.0, -1.0, -1.0 },{ 2.0, 2.0, -1.0 },{ -2.0, 2.0, -1.0 }
    };

        glPushMatrix();

            //glColor3f(0.0f, 0.0f, 1.0f);

            glTranslatef(position_x+13, position_y, position_z);

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

        glPopMatrix();


        glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
        /*glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);
        */
        glColor3f(1.0f, 1.0f, 1.0f);

}


void building::readImage(char* filename, GLbyte data[256][256][3]) {
  FILE *file;

  file = fopen(filename, "rb");
  if (file != NULL) {
    fread(data, 256 * 256 * 3, 1, file);
    fclose(file);
  } else {

  }
}

int* building::readImageTGA(char* filename, unsigned char *data )
{
    FILE *filePtr;
    unsigned char imageTypeCode;
    short int imageWidth;
    short int imageHeight;
    unsigned char bitCount;


    unsigned char ucharBad;
    short int sintBad;
    long imageSize;
    int colorMode;
    unsigned char colorSwap;

    filePtr = fopen(filename, "rb");

    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

    // Which type of image gets stored in imageTypeCode.
    fread(&imageTypeCode, sizeof(unsigned char), 1, filePtr);

    // For our purposes, the type code should be 2 (uncompressed RGB image)
    // or 3 (uncompressed black-and-white images).
    if (imageTypeCode != 2 && imageTypeCode != 3)
    {
        fclose(filePtr);
        //return false;
    }

    // Read 13 bytes of data we don't need.
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);

    // Read the image's width and height.
    fread(&imageWidth, sizeof(short int), 1, filePtr);
    fread(&imageHeight, sizeof(short int), 1, filePtr);

    // Read the bit depth.
    fread(&bitCount, sizeof(unsigned char), 1, filePtr);

    // Read one byte of data we don't need.
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

    // Color mode -> 3 = BGR, 4 = BGRA.
    colorMode = bitCount / 8;
    imageSize = imageWidth * imageHeight * colorMode;

    // Allocate memory for the image data.
    data = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);

    // Read the image data.
    fread(data, sizeof(unsigned char), imageSize, filePtr);

    // Change from BGR to RGB so OpenGL can read the image data.
    for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
    {
        colorSwap = data[imageIdx];
        data[imageIdx] = data[imageIdx + 2];
        data[imageIdx + 2] = colorSwap;
    }
    fclose(filePtr);


    int aSize[2] = {imageWidth, imageHeight};

    return aSize;

}



/*
typedef struct
{
    unsigned char imageTypeCode;
    short int imageWidth;
    short int imageHeight;
    unsigned char bitCount;
    unsigned char *imageData;
} TGAFILE;

bool LoadTGAFile(char *filename, TGAFILE *tgaFile)
{
    FILE *filePtr;
    unsigned char ucharBad;
    short int sintBad;
    long imageSize;
    int colorMode;
    unsigned char colorSwap;

    // Open the TGA file.
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
    {
        return false;
    }

    // Read the two first bytes we don't need.
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

    // Which type of image gets stored in imageTypeCode.
    fread(&tgaFile->imageTypeCode, sizeof(unsigned char), 1, filePtr);

    // For our purposes, the type code should be 2 (uncompressed RGB image)
    // or 3 (uncompressed black-and-white images).
    if (tgaFile->imageTypeCode != 2 && tgaFile->imageTypeCode != 3)
    {
        fclose(filePtr);
        return false;
    }

    // Read 13 bytes of data we don't need.
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);

    // Read the image's width and height.
    fread(&tgaFile->imageWidth, sizeof(short int), 1, filePtr);
    fread(&tgaFile->imageHeight, sizeof(short int), 1, filePtr);

    // Read the bit depth.
    fread(&tgaFile->bitCount, sizeof(unsigned char), 1, filePtr);

    // Read one byte of data we don't need.
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

    // Color mode -> 3 = BGR, 4 = BGRA.
    colorMode = tgaFile->bitCount / 8;
    imageSize = tgaFile->imageWidth * tgaFile->imageHeight * colorMode;

    // Allocate memory for the image data.
    tgaFile->imageData = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);

    // Read the image data.
    fread(tgaFile->imageData, sizeof(unsigned char), imageSize, filePtr);

    // Change from BGR to RGB so OpenGL can read the image data.
    for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
    {
        colorSwap = tgaFile->imageData[imageIdx];
        tgaFile->imageData[imageIdx] = tgaFile->imageData[imageIdx + 2];
        tgaFile->imageData[imageIdx + 2] = colorSwap;
    }

    fclose(filePtr);
    return true;
}
*/