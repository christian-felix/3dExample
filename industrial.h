#define INDUSTRIAL_H
#include <GLUT/glut.h>

class industrial {

    private:

        GLuint width;
        GLuint height;
        GLuint depth;

        float position_x;
        float position_y;
        float position_z;

        GLuint front_texture;
        char *front_bitmap;

        GLuint left_texture;
        char *left_bitmap;

        GLuint right_texture;
        char *right_bitmap;

        GLuint back_texture;
        char *back_bitmap;

        //char* front_filename = "images/industrial_building.tga";

    public:
        industrial();
        void drawIndustrial();
        void drawIndustrialFront();
        void drawIndustrialSide();
        char* readTgaImage(char* filename, char *bitmap);
};
