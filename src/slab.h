#include "main.h"

#ifndef SLAB_H
#define SLAB_H

class Slab {
public:
    Slab() {}
    Slab(float x, float y, float l, float b, float speed, float speed_y);
    glm::vec3 position;
    float length;
    float breadth;
    float rotation;
    float speed;
    float speed_y;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // SLAB_H

