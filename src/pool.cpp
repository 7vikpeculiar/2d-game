#include "pool.h"
#include "main.h"

Pool::Pool(float x, float y, float radius) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 180;
    this->radius = radius;
    //speed = 0.01;
    //speed_y = 0.1;
    static GLfloat vertex_buffer_data[185*9];
    int theta = 0,array_iter = 0;
    for(int count = 0; count<=180; count++)
    {
        vertex_buffer_data[array_iter]=0.0;
        vertex_buffer_data[array_iter+1]=0.0;
        vertex_buffer_data[array_iter+2]=0.0;
        vertex_buffer_data[array_iter+3]=radius *cos(3.1415*theta/180);
        vertex_buffer_data[array_iter+4]=radius *sin(3.1415*theta/180);
        vertex_buffer_data[array_iter+5]=0;
        vertex_buffer_data[array_iter+6]=radius*cos(3.1415*(theta+1)/180);
        vertex_buffer_data[array_iter+7]=radius*sin(3.1415*(theta+1)/180);
        vertex_buffer_data[array_iter+8]=0;
        array_iter += 9; https://goo.gl/forms/53fzG0fkY2osuxXu1
        theta += 1;
    }
    this->object = create3DObject(GL_TRIANGLES, 180*3, vertex_buffer_data, COLOR_BLUE, GL_FILL);
}

void Pool::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP* Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Pool::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

/*void Pool::tick() {
    /*this->position.x -= speed;
    if(this->position.y > -2)
    { this->position.y += speed_y;
     this->speed_y -= 0.01;
    }
    if(this->position.y < -2)
    {
        this->position.y = -2;
        this->speed_y = 0.1;
    }
}*/

bounding_circle_t Pool::bounding_circle() {
    float x = this->position.x, y = this->position.y, r = this->radius;
    bounding_circle_t bbox = { x, y, r };
    return bbox;
}



