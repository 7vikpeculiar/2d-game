#include "spikes.h"
#include "main.h"

Spike::Spike(float x, float y,float length, float height, float max_traversal, float speed) {
    this->position = glm::vec3(x, y, 0);
    this->original_x = x;
    this->rotation = 0;
    this->speed = speed;
    this->time = 1000;
    this->max_traversal = max_traversal;
    // speed_y = 0.0;
   // this->ground = 2.0;
   // this->gravity = 0.01;
    this->length = length;
    this->height = height;
    float l = length;
    float h = height;
    GLfloat vertex_buffer_data[] =
    {
        l/2 ,  0.0f ,0.0f,
       -l/2 ,  0.0f ,0.0f,
        0   ,  h  ,0.0f,

        l/2 ,  0.0f ,0.0f,
       3*l/2 , 0.0f ,0.0f,
        l ,    h    ,0.0f,

        -l/2 ,  0.0f ,0.0f,
       -3*l/2 , 0.0f ,0.0f,
        -l ,    h    ,0.0f,

    };


    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Spike::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Spike::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Spike::tick() {
    if(fabs(this->position.x - this->original_x) > this->max_traversal)
    {
        this->speed  = -speed;
    }
    this->position.x -= this->speed;
    this->time -=1;

 }

bounding_box_t Spike::bounding_box() {
   float x = this->position.x, y = this->position.y, h = this->height , l = this->length;
   bounding_box_t bbox = { x, y, 3*l, h};
    return bbox;
}

