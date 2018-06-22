#include "floor.h"
#include "main.h"

Floor::Floor(float x, float y, float l,float b, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->length = l;
    this->breadth = b;
    //speed = 0.01;
    //speed_y = 0.1;
    GLfloat vertex_buffer_data[]=
    {
        l/2 ,  b/2 ,0.0f,
        l/2 , -b/2 ,0.0f,
       -l/2, -b/2 ,0.0f,

       -l/2 , -b/2 ,0.0f,
        l/2 ,  b/2 ,0.0f,
       -l/2 ,  b/2 ,0.0f,

    };

   this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Floor::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Floor::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


bounding_box_t Floor::bounding_box() {
    float x = this->position.x, y = this->position.y, l = this->length, b = this->breadth ;
    bounding_box_t bbox = { x, y, l, b};
    return bbox;
}
