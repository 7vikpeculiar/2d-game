#include "player.h"
#include "main.h"

Player::Player(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.1;
    speed_y = 0.0;
    this->ground = 2.0;
    this->gravity = 0.01;
    this->force = 0.0001;
    this->magnet = 0;
    static GLfloat vertex_buffer_data[3330];
    int sides = 361;
    int array_iter = 0, theta = 0;
    float radius = this->radius = 0.25;
    for(int count = 0; count<= sides; count++)
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
        array_iter += 9;
        theta += 1;
    }

    this->object = create3DObject(GL_TRIANGLES, 361*3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick() {
    //int ground = global_ground;
    this->position.x -= this->speed;
    //this->speed -= force;
    // Finding pool
    if(this->position.x > -2.8 && this->position.x < -1.2) // in water column
    {

        float x_co = fabs(this->position.x+2.0) ;
        //std::cout << x_co;
        float pool_radius_square = 0.8*0.8;
        float y_co = pow(pool_radius_square - (x_co*x_co),0.5);
        //std::cout << pool_radius_square -x_co*x_co ;
        this->ground = -2.0 - y_co ;

        //std::cout << this->ground;
    }
    else
    {
        this->ground = -2;
     //   this->gravity = 0.01;
    }
    // Assigning proper gravity

    if(this->position.x > -2.8 && this->position.x < -1.2 && this->position.y < -2 && this->speed_y < 0)
    {
        this->speed = 0.001*(this->position.x + 2.0)/fabs(this->position.x + 2.0);
        this->speed_y = -0.01;
        this->gravity = 0.1*speed_y;
    }else if(this->position.x > -2.8 && this->position.x < -1.2 && this->position.y < -2 && this->speed_y > 0)
    {
        this->speed_y = 0.025;
        this->gravity = 0;
    }
    else if(this->magnet == 0)
    {
        this->speed = 0;
        this->gravity = 0.01;
    }

  /*  if((this->magnet == 1 || this->magnet == -1 )&& this->position.y > -2.8 && this->speed_y > 0)
    {

        this->speed_y = 0;
    }*/
    //Normal ticking
    if(this->position.y > this->ground)
    {
         this->position.y += speed_y;
         this->speed_y -= this->gravity;
    }

    if(this->position.y < this->ground) // and not in water column
    {
        this->position.y = this->ground;
    }

    if(this->magnet != 0)
    {
       // std::cout << 1;
        this->speed += this->force*this->magnet;
    }
   // std::cout << this->gravity << this->ground;
    /*if((this->magnet == 1 || this->magnet == -1 )&& this->gravity  == 0 && this->position.y > -2.8)
    {
        this->gravity = 0.01;
      //  this->speed_y = 0.0;// Magnet present and ball is outside;
    }*/
  //  std::cout << this->speed;
    // if in water column --> Follow circular path

}

 bounding_circle_t Player::bounding_circle() {
    float x = this->position.x, y = this->position.y, r = this->radius ;
    bounding_circle_t bbox = { x, y, r};
    return bbox;
}

