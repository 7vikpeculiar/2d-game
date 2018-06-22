#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>
//#include <bits/stdc++.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float width;
    float height;
};

struct bounding_circle_t
{
    float x;
    float y;
    float r;
};

struct bounding_magnet_t
{
    float x;
    int direction;
};
//qint score_print = 0;
int detect_collision(bounding_box_t a, bounding_box_t b);
int detect_ball_collision(bounding_circle_t a, bounding_circle_t b);
int detect_trampoline_collision(bounding_circle_t a, bounding_circle_t b);
int detect_pool_collision(bounding_circle_t a,bounding_circle_t b);
int detect_spike_collision(bounding_box_t a, bounding_circle_t b);
int detect_magnet_collision(bounding_magnet_t a, bounding_circle_t b);
int detect_walls(bounding_circle_t a);

//string int_to_str(int num);

extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();


//bool surface = true;
// ---- Colors ----
extern const color_t COLOR_RED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_BROWN;
extern const color_t COLOR_PARROT_GREEN;
extern const color_t COLOR_MAGNA_RED;

extern const color_t COLOR_VIOLET;
extern const color_t COLOR_INDIGO;
extern const color_t COLOR_RBLUE;
extern const color_t COLOR_RGREEN;
extern const color_t COLOR_YELLOW;
extern const color_t COLOR_ORANGE;
extern const color_t COLOR_RRED;

#endif
