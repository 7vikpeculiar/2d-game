#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, float radius, float length, float breadth, int direction);
    glm::vec3 position;
    float rotation;
    float radius;
    float length;
    float breadth;
    int direction;
    int time;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    //void tick();
    //double speed;
    //double speed_y;
    bounding_magnet_t bounding_line();
    void tick();
private:
    VAO *object;
};

#endif // TRAMPOLINE_H
