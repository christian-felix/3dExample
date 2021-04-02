#define VEHICLE_H
#include <GLUT/glut.h>

class vehicle {

    private:

        GLuint texture;
        GLbyte image[256][256][3];

        float speed;
        float direction;  //current driving direction
        float angle;      //angle of the front tires

        float position_x;
        float position_y;
        float position_z;

        float length;
        float width;
        float height;

    public:
        vehicle();

        void drawVehicle();
        void drawTires();
        void drawSeats();
        void drawDoors();

        void startVehicle();
        void stopVehicle();

        void moveForward();
        void moveBackward();

        void turnLeft();
        void turnRight();

        void readImage(char* filename, GLbyte data[256][256][3]);
        void addTexture();

        void accelerate();
        void braking();
        float getSpeed();
};