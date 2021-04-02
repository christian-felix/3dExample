#define BUILDING_H
#include <vector>
#include <GLUT/glut.h>

using namespace std;

class building
{
    private:

        GLuint texture;
        GLuint texture2;
        GLbyte image[256][256][3];
        unsigned char *imageData;

        float position_x;
        float position_y;
        float position_z;

        int w;
        int h;

        vector<GLint> front; //{0,1,2,3};
        vector<GLfloat> vertices; // = {{ -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 },{ 1.0, 1.0,-1.0 },{ 1.0, 1.0, -1.0 }};

    public:
        building();
        void drawBuilding();
        void drawBuilding2();
        void readImage(char* filename, GLbyte data[256][256][3]);
        int* readImageTGA(char* filename, unsigned char* data);


};