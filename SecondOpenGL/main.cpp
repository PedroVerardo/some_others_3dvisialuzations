#ifdef _WIN32
#include <windows.h>

// Choose glad or glew to initialize OpenGL context on Windows
#include <gl/glew.h>

#include <GLFW/glfw3.h>

#else

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#endif


#include "error.h"
#include "buffer.h"
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.141593
static GLuint vao;
static GLuint pid;
const int definition = 100;

static GLuint createScene(void)
{
    
    float r = 0.5f;
    float x = 0.0f;
    float y = 0.0f;

    // Calcular os vértices do círculo
    float circleVertices[definition * 2];
    for (int i = 0; i < definition; ++i) {
        float dgree = 2.0 * M_PI * float(i) / float(definition);
        circleVertices[i * 2] = (r * cos(dgree) + x)/2;
        circleVertices[i * 2 + 1] = (r * sin(dgree) + y)/2;
    }
    for (int i = 0; i < definition; i++) {
        printf("%f", circleVertices[i]);
    }
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint id[1];
    glGenBuffers(1, id);
    glBindBuffer(GL_ARRAY_BUFFER, id[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    return vao;
}

static int buildProgram()
{
    GLuint vid = CreateShader(GL_VERTEX_SHADER, "vertex.glsl");
    GLuint fid = CreateShader(GL_FRAGMENT_SHADER, "fragment.glsl");
    return CreateProgram(vid, fid, 0);
}

static void initialize()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    vao = createScene();
    pid = buildProgram();
}

static void error(int code, const char* msg)
{
    printf("GLFW error %d: %s\n", code, msg);
    glfwTerminate();
    exit(1);
}

static void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void resize(GLFWwindow* win, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void display(GLFWwindow* win, int time)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(pid);

    //#####Create Earth########
    float color_earth[] = {0.0f,0.0f,1.0f,1.0f};
    GLint loc_earth_color = glGetUniformLocation(pid, "uniformColor");
    glUniform4fv(loc_earth_color, 1, color_earth);

    glm::mat4 M(1.0f);
    glm::vec3 t(0.6f, 0.0f, 0.0f);
    glm::vec3 s(0.5f,0.5f,0.5f);
    float angulo = time/8.0f;

    //M = glm::ortho(0, 10, 0, 10);
    M = glm::rotate(M, angulo, glm::vec3(0.0f, 0.0f, 1.0f));
    M = glm::translate(M, t);
    glm::mat4 M_ref_lua = M;
    M = glm::rotate(M, angulo*4, glm::vec3(0.0f, 0.0f, 1.0f));
    M = glm::scale(M, s);
    

    GLint loc_earth_matrix = glGetUniformLocation(pid, "matx");
    glUniformMatrix4fv(loc_earth_matrix, 1, GL_FALSE, glm::value_ptr(M));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, definition);

    //######Create Sum########
    float color_sum[] = { 1.0f,1.0f,0.0f,1.0f };
    GLint loc_sum_color = glGetUniformLocation(pid, "uniformColor");
    glUniform4fv(loc_sum_color, 1, color_sum);

    glm::mat4 M2(1.0f);
    glm::vec3 t2(0.0f, 0.0f, 0.0f);
    glm::vec3 s2(1.0f, 1.0f, 1.0f);
    float angulo2;

    M2 = glm::translate(M2, t2);
    M2 = glm::scale(M2, s2);
    //M = glm::rotate(M, angulo, t);
    //M2 = glm::ortho(0, 10, 0, 10);

    GLint loc_sum_matrix = glGetUniformLocation(pid, "matx");
    glUniformMatrix4fv(loc_sum_matrix, 1, GL_FALSE, glm::value_ptr(M2));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, definition);

    //#####Create Moon########
    float color_moon[] = {0.22f,0.22f,0.22f,1.0f};
    GLint loc_moon_color = glGetUniformLocation(pid, "uniformColor");
    glUniform4fv(loc_moon_color, 1, color_moon);
    
    glm::mat4 M3 = M_ref_lua;
    glm::vec3 t3(0.25f, 0.0f, 0.0f);
    glm::vec3 s3(0.5f, 0.5f, 0.5f);
    float angulo3 = time/17.0f;

    M3 = glm::rotate(M3, angulo3, glm::vec3(0.0f, 0.0f, 1.0f));
    M3 = glm::translate(M3, t3);
    M3 = glm::scale(M3, s3);
    //M2 = glm::ortho(0, 10, 0, 10);

    GLint loc_moon_matrix = glGetUniformLocation(pid, "matx");
    glUniformMatrix4fv(loc_moon_matrix, 1, GL_FALSE, glm::value_ptr(M3));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, definition);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);       // required for mac os
    //glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER,GLFW_TRUE);  // option for mac os

    //glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

    glfwSetErrorCallback(error);

    GLFWwindow* win = glfwCreateWindow(600, 400, "Window title", nullptr, nullptr);
    glfwSetFramebufferSizeCallback(win, resize);  // resize callback
    glfwSetKeyCallback(win, keyboard);            // keyboard callback

    glfwMakeContextCurrent(win);

#ifdef __glad_h_
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD OpenGL context\n");
        exit(1);
    }
#endif
#ifdef __glew_h__
    glewInit();
    if (glewInit() != GLEW_OK) {
        printf("Failed to initialize GLEW OpenGL context\n");
        exit(1);
    }
#endif

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    initialize();
    int cont = 0;
    int timer = 0;
    while (!glfwWindowShouldClose(win)) {
        if (timer == 10) { 
            timer = 0;
            cont++;
        }
        //idle(win);
        display(win,cont);
        glfwSwapBuffers(win);
        glfwPollEvents();
        timer++;
        
    }
    glfwTerminate();
    return 0;
}
