
// Faces of the cube
GLint faces[][4] = { { 4, 5, 6, 7 }, { 1, 2, 6, 5 },
 { 0, 1, 5, 4 }, { 0, 3, 2,1 }, { 0, 4, 7, 3 }, { 2, 3, 7, 6 } };

// Vertices
GLfloat vertices[][3] = {
    { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0,-1.0 },{ -1.0, 1.0, -1.0 },
     { -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0,1.0, 1.0 }, { -1.0, 1.0, 1.0 }
 };


void bindTextureTorus()
{
    GLuint texture;
    GLbyte image[256][256][3];

    readRAWImage("images/tireOne.tga", image);

    //glCullFace(GL_FRONT);
    //glEnable(GL_CULL_FACE);

    //load texture (tire)
    //glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    // Create the texture object
    //glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    /*glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    */

    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(-1.0,1.0, -1.0);
        //glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glutSolidTorus(0.2, 0.5, 20, 25);
        //glutSolidCube(4);
    glPopMatrix();

    glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);

    glDisable(GL_TEXTURE_2D);
    //glDisable(GL_CULL_FACE);
}



void bindCube() {

  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);

  // Read the images
  GLbyte image[6][256][256][3];
  readRAWImage("images/brownpaper.raw", image[1]);
  readRAWImage("images/flagstone.raw", image[2]);
  readRAWImage("images/brick.raw", image[0]);
  readRAWImage("images/frostedglass.raw", image[3]);
  readRAWImage("images/lake.raw", image[4]);
  readRAWImage("images/oak.raw", image[5]);

  // Get "names" for the textures
  glGenTextures(6, textureNames);

  for (int i = 0; i < 6; i++) {
    // Select the texture object
    glBindTexture(GL_TEXTURE_2D, textureNames[i]);

    // Set the parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Create the texture object
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, image[i]);
  }

  // Enable textures
  //glEnable(GL_TEXTURE_2D);
}


/**
 * The display callback.
 */
void drawCube() {
  // Clear the screen
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glTranslatef(7.5,1.5,-2);

      // Create the cube
      for (int f = 0; f < 6; f++) {
        // Select a texture object
        glBindTexture(GL_TEXTURE_2D, textureNames[f]);

        // Create the face
        glBegin(GL_QUADS);
        int v;

        v = faces[f][0];
        glTexCoord2f(0.0, 0.0);  // Use bottom left texel
        glVertex3fv(vertices[v]);

        v = faces[f][1];
        glTexCoord2f(0.0, 1.0);  // Use bottom right texel
        glVertex3fv(vertices[v]);

        v = faces[f][2];
        glTexCoord2f(1.0, 1.0);  // Use top right texel
        glVertex3fv(vertices[v]);

        v = faces[f][3];
        glTexCoord2f(1.0, 0.0);  // Use top left texel
        glVertex3fv(vertices[v]);

        glEnd();
      }

      // Force the rendering (off-screen)
      glFlush();

  // Handle the double buffering
  //glutSwapBuffers();
}

