#include "main.h"

#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H


class Trampoline {
public:
    Trampoline() {}
    Trampoline(float x, float y, float radius, float length, float breadth);
    glm::vec3 position;
    float rotation;
    float radius;
    float length;
    float breadth;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    //void tick();
    //double speed;
    //double speed_y;
    bounding_circle_t bounding_circle();
private:
    VAO *object;
};

#endif // TRAMPOLINE_H
