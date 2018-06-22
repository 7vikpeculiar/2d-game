#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color, float radius, float speed, float speed_y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = speed;
    this->speed_y = speed_y;
    static GLfloat vertex_buffer_data[3330];
    int sides = 361;
    int array_iter = 0, theta = 0;
    float radi  = this->radius = radius;
    for(int count = 0; count<= sides; count++)
    {
        vertex_buffer_data[array_iter]=0.0;
        vertex_buffer_data[array_iter+1]=0.0;
        vertex_buffer_data[array_iter+2]=0.0;
        vertex_buffer_data[array_iter+3]=radi *cos(3.1415*theta/180);
        vertex_buffer_data[array_iter+4]=radi *sin(3.1415*theta/180);
        vertex_buffer_data[array_iter+5]=0;
        vertex_buffer_data[array_iter+6]=radi*cos(3.1415*(theta+1)/180);
        vertex_buffer_data[array_iter+7]=radi*sin(3.1415*(theta+1)/180);
        vertex_buffer_data[array_iter+8]=0;
        array_iter += 9;
        theta += 1;
    }

    this->object = create3DObject(GL_TRIANGLES, 361*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->position.x += speed;
 }

bounding_circle_t Ball::bounding_circle() {
    float x = this->position.x, y = this->position.y, r = this->radius;
    bounding_circle_t bbox = { x, y, r};
    return bbox;
}
