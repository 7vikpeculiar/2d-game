#include "main.h"

#ifndef SPIKE_H
#define SPIKE_H


class Spike {
public:
    Spike() {}
    Spike(float x, float y, float length, float height, float max_traversal, float speed);
    glm::vec3 position;
    float rotation;
    float time;
    float max_traversal;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float length;
    float height;
    double speed;
    float original_x;
    //double speed_y;
    //float ground;
    //float gravity;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // PLAYER_H
