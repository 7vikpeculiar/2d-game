#include "main.h"

#ifndef FLOOR_H
#define FLOOR_H


class Floor {
public:
    Floor() {}
    Floor(float x, float y, float l, float b, color_t color);
    glm::vec3 position;
    float length;
    float breadth;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // FLOOR_H

