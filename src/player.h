#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double speed_y;
    float ground;
    float gravity;
    float force;
    int magnet;
    bounding_circle_t bounding_circle();
private:
    VAO *object;
};

#endif // PLAYER_H
