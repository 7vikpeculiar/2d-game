#include "main.h"
#include "timer.h"
#include "ball.h"
#include "pool.h"
#include "floor.h"
#include "player.h"
#include "slab.h"
#include "trampoline.h"
#include "spikes.h"
#include "magnet.h"
//#include "digits.h"
//#include "line.h"
//#include "score.h"
using namespace std;
//int score = 0;
//int level  = 0;
GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

// Random Generation

glm::mat4 VP; // Globalized VP
/**************************
* Customizable functions *
**************************/

Player ball1;
//Ball ball2;
Pool pool1;
Floor floor1;
Floor floor2;
std::vector <Ball> panels;
std::vector <Ball>::iterator iter;
std::vector <Slab> slabs;
std::vector <Spike> porcups;
std::vector <Magnet> jedi;
color_t colorarray[] = {COLOR_VIOLET,COLOR_INDIGO,COLOR_RBLUE,COLOR_RGREEN,COLOR_YELLOW,COLOR_ORANGE,COLOR_RED};
//Slab slab1;
Trampoline tramp1;
//Spike porky;
//Magnet magna;
int score = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
Timer t60(1.0 / 60);
Timer t1min(30);
Timer t34min(10);
int score_print = 0;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in throtatee frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    VP = Matrices.projection * Matrices.view;

    // Matrices.view = glm::lookAt( eye, target, up )
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;
// MVP = Projection * View * Model

    // Scene render

    floor1.draw(VP);
    floor2.draw(VP);
    pool1.draw(VP);
    ball1.draw(VP);
    //ball2.draw(VP);
    for(int i=0;i<panels.size();i++)
    {
        panels[i].draw(VP);
    }
    //slab1.draw(VP);
    tramp1.draw(VP);
    //porky.draw(VP);
    for(int i=0;i<porcups.size();i++)
    {
        porcups[i].draw(VP);
    }
    for(int i=0;i<jedi.size();i++)
    {
        jedi[i].draw(VP);
    }
    //magna.draw(VP);
    //score.draw(VP);

}

string int_to_str(int num)
{
    stringstream ss;

    ss << num;

    return ss.str();
}

//void panel_position()
int flag = 0;

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int top = glfwGetKey(window, GLFW_KEY_SPACE);
    int zee = glfwGetKey(window,GLFW_KEY_Z);
    //glfwSetScrollCallback(window,scroll_callback);
    if (left) {
        // Do something
        ball1.position[0] -= 0.1;
    }
    if(right){
        ball1.position[0] += 0.1;
    }
    if(top && ball1.position.y == ball1.ground){
        ball1.speed_y = 0.21;
        ball1.position.y += 0.01;
    }
    if(zee)
        {

        if(screen_zoom < 1.6 && flag == 0){
            screen_zoom += 0.05;
        }
        else if(flag == 0 && screen_zoom == 1.5){
            flag = 1;
        }

        if(flag == 1 && screen_zoom > 0.4)
        {
            screen_zoom -= 0.05;
        }
        else if(screen_zoom == 0.5 && flag == 1)
        {
            flag = 0;
        }
        //screen_zoom += 0.1 ;
        reset_screen();
    }
}

void create_random_balls(vector<Ball>& looper)
{
    float screen_size = -4.5;
    float min_height = -1.5;
    float min_radius = 0.2;
    float speed_y = 0;
    float min_speed_x = 0.01;
    int index = (rand()%7);
    //srand(time(NULL));
    vector <Ball>::iterator iterer;
    if(looper.size() < 12)
    {
       float x = screen_size;
       float y = min_height + (rand()%55)/10.0;
       float r = 0.2 + (rand()%4)/10.0;
       float speed_x = min_speed_x + (rand()%10)/100.0;
       iterer = looper.begin();
       looper.insert(iterer,Ball(x,y,colorarray[index],r,speed_x,speed_y));
       looper[0].draw(VP);
    }
}

void create_random_porcups(vector<Spike>& looper)
{
    //float screen_size = ;
  // int timer = rand()%1000;
   // if(timer != 1){return;}
    float height = -2.25;
    float speed_x = 0.01;
    float min_dist_traversal = 0.2;
    //srand(time(NULL));
    vector <Spike>::iterator iterer;
    if(looper.size() < 1)
    {
       float x = 0 + (rand()%4)/10.0;
       float speed_x = speed_x + (rand()%10)/100.0;
       iterer = looper.begin();
       looper.insert(iterer,Spike(x,height,0.25,0.25,speed_x*50,speed_x));
       looper[0].draw(VP);
    }
   // porky  = Spike(0,-2.25,0.25,0.25,0.5,0.01);

}
void create_random_jedi(vector<Magnet>& looper)
{
    //float screen_size = ;
  // int timer = rand()%1000;
   // if(timer != 1){return;}
    float height =0 + (rand()%35)/10.0;
    int direction = -1;
    if((rand()%2))
    {
        direction *= -1;
    }
    //cout << direction;
    vector <Magnet>::iterator iterer;
    if(looper.size() < 1)
    {
       iterer = looper.begin();
       looper.insert(iterer,Magnet(-3.2*direction,height,0.5,0.8,0.3,direction));
       looper[0].draw(VP);
       ball1.magnet = direction;
    }
   //    magna  = Magnet(-3.2,2,0.5,0.5,0.25);


}
void delete_invalid_balls(vector<Ball>& looper)
{
    for(int i=0; i< looper.size();i++)
    {
        if(looper[i].position.x > 7)
        {
            looper.erase(looper.begin() + i);
            return;

        }
    }
}
void delete_invalid_porcups(vector<Spike>& looper)
{
    for(int i=0; i< looper.size();i++)
    {
        if(looper[i].time < 0)
        {
            looper.erase(looper.begin() + i);
            return;

        }
    }
}
void delete_invalid_jedi(vector<Magnet> &looper)
{
    for(int i=0; i< looper.size();i++)
    {
        if(looper[i].time < 0)
        {
            looper.erase(looper.begin() + i);
            ball1.magnet = 0;
            //ball1.gravity = 0.01;
            return;

        }
    }
}
float collision_correction(Player* a, Ball *b)
{
    //Player winston = *a;
    //Ball  obstacle = *b;

        float dist = pow(((a->position.x - b->position.x)*(a->position.x - b->position.x)
                         + (a->position.y - b->position.y)*(a->position.y - b->position.y)),0.5);
        float cos_t = (a->position.x - b->position.x)/dist;
        float sin_t = (a->position.y - b->position.y)/dist;
        a->position.x = (a->radius + b->radius)*cos_t;
        a->position.y = (a->radius + b->radius)*sin_t;
        //float slope = (a->position.y - b->position.y)/(a->position.x - b->position.x);
        //return atan(slope);

}

void ball_collision_movement(vector<Ball>& looper , Player* player_pointer)
{
    Player winston = *player_pointer ;
    int end = looper.size();
    for(int i=0;i< looper.size();i++)
    {
        if(detect_ball_collision(looper[i].bounding_circle(),winston.bounding_circle()) && winston.speed_y < 0)
        {
            winston.speed_y += 0.2;
            looper.erase(looper.begin() + i);
            score += 1;
            cout << score;
        }
            //score.draw(VP);

            }

    *player_pointer = winston;

    return;
}

void trampoline_collision_movement(Player* player_pointer, Trampoline* trampoline_pointer)
{
    Player winston = *player_pointer ;
    Trampoline trampy = *trampoline_pointer;
    if(detect_trampoline_collision(winston.bounding_circle(),trampy.bounding_circle()) && winston.speed_y < 0)
        {
            winston.speed;
            winston.speed_y = -winston.speed_y + 0.03 ;
           // cout << i << endl;
            //looper.erase(looper.begin() + i);}
            //cout << looper.size() << endl;

            }

    *player_pointer = winston;

    return;
}

void pool_collision_movement(Player* player_pointer, Pool* pool_pointer)
{
    Player winston  = *player_pointer;
    Pool aqua = *pool_pointer;
    if(detect_pool_collision(winston.bounding_circle(),aqua.bounding_circle()))
    {
        //
    }
}

void porcups_collision_movement(vector<Spike>& looper , Player* player_pointer)
{
    Player winston = *player_pointer ;
    int end = looper.size();
    for(int i=0;i< looper.size();i++)
    {
        if(detect_spike_collision(looper[i].bounding_box(),winston.bounding_circle()))
        {
            //winston.speed_y += 0.2;
            looper.erase(looper.begin() + i);}
            score -=5 ;
            cout << score;
            //score.draw(VP);

            }

    *player_pointer = winston;

    return;
}

void jedi_collision_movement(vector<Magnet>& looper , Player* player_pointer)
{
    Player winston = *player_pointer ;
    for(int i=0;i< looper.size();i++)
    {
        if(detect_magnet_collision(looper[i].bounding_line(),winston.bounding_circle()))
        {
            //winston.speed_y += 0.2;
            winston.magnet = 0;
            looper.erase(looper.begin() + i);}


        }

    *player_pointer = winston;

    return;
}

void walls_collision_movement(Player *player_pointer)
{
    Player winston = *player_pointer ;
    if(detect_walls(winston.bounding_circle()))
        {
            //winston.speed_y += 0.2;
            cout << 1;
            if (abs(winston.position.x) > 3.8)
            {
                winston.position.x = 3.8*(abs(winston.position.x)/winston.position.x);
            }
            if (abs(winston.position.y) > 3.8)
            {
                winston.speed_y = -abs(winston.speed_y);
            }
        }

    *player_pointer = winston;

    return;
}
void tick_elements() {
    ball1.tick();
    //ball2.tick();
    //pool1.tick();
    for(int i=0;i<panels.size();i++)
    {
        panels[i].tick();
    }

    ball_collision_movement(panels,&ball1);
    trampoline_collision_movement(&ball1,&tramp1);
    porcups_collision_movement(porcups,&ball1);
    jedi_collision_movement(jedi,&ball1);
    walls_collision_movement(&ball1);
    for(int i=0;i<porcups.size();i++)
    {
        porcups[i].tick();
    }
    for(int i=0;i<jedi.size();i++)
    {
        jedi[i].tick();
    }
    //porky.tick();
    //magna.tick();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    ball1       = Player(1, 0);
    //ball2       = Ball(-2, 2, COLOR_RED,0.8,0,0);
    //ball2.speed = 0;
    ball1.speed = 0;
    float grass = 3;
    floor2 = Floor(0,-2.5,8,0.5,COLOR_GREEN);
    floor1 = Floor(0,-3.5,8,1.5,COLOR_BLACK);
    pool1 = Pool(-2,-2.24,0.8);
    //slab1  = Slab(2,2,0.3,0.8*18/5,0,0);
    float xpos = -4, ypos = -0.1;
   /* for(int i=0;i<7;i++)
    {
       iter = panels.begin();
       panels.insert(iter,Ball(xpos,ypos,COLOR_BLUE,0.25,0,0));
        xpos += 0.5;
    }*/
    tramp1 = Trampoline(2,-1.5,0.6,0.8,0.1);
    //porky  = Spike(0,-2.25,0.25,0.25,0.5,0.01);
    //magna  = Magnet(-3.2,2,0.5,0.8,0.3,1);
    //ball1.force = 0.0001;

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
    //scorea.update(0);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
      if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            create_random_balls(panels);
            delete_invalid_balls(panels);
            if(t1min.processTick()){
            create_random_porcups(porcups);
            }
            delete_invalid_porcups(porcups);
            if(t34min.processTick())
            {
                create_random_jedi(jedi);

            }
            delete_invalid_jedi(jedi);
            //window.glutSetWindowTitle("yo");
            tick_input(window);
            //scroll_callback(window,);
        }
        //glfwSetWindowTitle(window, "Lala");
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

int detect_collision(bounding_box_t a, bounding_box_t b) {
    /*return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));*/
    if((abs(a.x-b.x)*2 < (a.width + b.width)) && (abs(a.y - b.y)*2 < (a.height+b.height)))
    {
        if(a.y >= -2+ (b.height)/2){return -1;}
        return 1;
    }
    return 0;
}

int detect_ball_collision(bounding_circle_t a, bounding_circle_t b)
{
    return (abs(a.x - b.x)  < (a.r + b.r)) &&
               (abs(a.y - b.y)  < (a.r + b.r)) && (b.y > (a.y + 0.1*a.r) );
}

int detect_trampoline_collision(bounding_circle_t a, bounding_circle_t b)
{
    return (abs(a.x - b.x)  < (a.r + b.r)) &&
               (abs(a.y - b.y)  < a.r) && (b.y > a.y);
}

int detect_pool_collision(bounding_circle_t a, bounding_circle_t b)
{
    return (abs(a.x - b.x)  < (a.r + b.r)) &&
               (abs(a.y - b.y)  < a.r) && (b.y > a.y);
}
int detect_spike_collision(bounding_box_t a, bounding_circle_t b)
{
    return (abs(a.y - b.y) < a.height + b.r) && (abs(a.x -  b.x) < b.r + a.width/2);
}
int detect_magnet_collision(bounding_magnet_t a, bounding_circle_t b)
{
    return ((b.x - a.x)*a.direction < 0);
}
int detect_walls(bounding_circle_t a)
{
    return abs(a.x) > 3.8 || abs(a.y) > 3.8;
}
void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}


