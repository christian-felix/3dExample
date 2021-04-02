#define HUMAN_H

class human {

    private:
        float position_x;
        float position_y;
        float position_z;
    public:
      human();
      void drawHead();
      void drawArms();
      void drawBody();
      void drawLegs();
};