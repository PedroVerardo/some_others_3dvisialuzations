
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "scene.h"
#include "state.h"
#include "camera.h"
#include "color.h"
#include "transform.h"
#include "error.h"
#include "shader.h"
#include "disk.h"
#include "triangle.h"
#include <vector>
#include <iostream>
#include <memory>

static ScenePtr scene;
static CameraPtr camera;

class MovePointer;
using MovePointerPtr = std::shared_ptr<MovePointer>;
class MovePointer : public Engine
{
    TransformPtr m_trf;
protected:
    MovePointer(TransformPtr trf)
        : m_trf(trf)
    {
    }
public:
    static MovePointerPtr Make(TransformPtr trf)
    {
        return MovePointerPtr(new MovePointer(trf));
    }
    virtual void Update(float dt)
    {
        m_trf->Rotate(-dt / 30.0f * 180.0f, 0, 0, 1);
    }
};

static void initialize(void)
{
    // set background color: white 
    glClearColor(0.8f, 1.0f, 1.0f, 1.0f);
    // enable depth test 
    glEnable(GL_DEPTH_TEST);

    // create objects
    camera = Camera::Make(0, 10, 0, 10);

    auto trf1 = Transform::Make();
    trf1->Translate(5, 5, -0.5);
    trf1->Scale(5, 5, 1);
    auto sun = Node::Make(trf1, {Color::Make(255,255,0) }, { Disk::Make() });
    auto trf2 = Transform::Make();
    trf2->Translate(1, 0, 1);
    auto trf3 = Transform::Make();
    trf3->Scale(0.7, 0.7, 1);
    auto earth = Node::Make(trf2, { Node::Make(trf3,{Color::Make(0,0,1)},{Disk::Make()}) });
    sun->AddNode(earth);
    auto trf4 = Transform::Make();
    auto trf5 = Transform::Make();
    trf5->Translate(1, 0.5, 0);
    trf4->MultMatrix(trf3->GetMatrix());
    trf4->Scale(0.5, 0.5, 1);
    auto moon = Node::Make(trf4, {Node::Make(trf5,{Color::Make(128,128,128)},{Disk::Make()})});
    earth->AddNode(moon);


    auto shader = Shader::Make();
    shader->AttachVertexShader("C:\\Users\\Pedro\\source\\repos\\SecondOpenGL\\SecondOpenGL\\vertex.glsl");
    shader->AttachFragmentShader("C:\\Users\\Pedro\\source\\repos\\SecondOpenGL\\SecondOpenGL\\fragment.glsl");
    shader->Link();

    // build scene

    auto root = Node::Make(shader, { sun });
    scene = Scene::Make(root);
    scene->AddEngine(MovePointer::Make(trf1));
    scene->AddEngine(MovePointer::Make(trf3));
    scene->AddEngine(MovePointer::Make(trf4));
}

static void display(GLFWwindow* win)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window 
    Error::Check("before render");
    scene->Render(camera);
    Error::Check("after render");
}

static void error(int code, const char* msg)
{
    printf("GLFW error %d: %s\n", code, msg);
    glfwTerminate();
    exit(0);
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

static void update(float dt)
{
    scene->Update(dt);
}

int main()
{
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(error);

    GLFWwindow* win = glfwCreateWindow(600, 400, "Window title", nullptr, nullptr);
    glfwSetFramebufferSizeCallback(win, resize);  // resize callback
    glfwSetKeyCallback(win, keyboard);            // keyboard callback

    glfwMakeContextCurrent(win);
    //printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    if (glewInit() != GLEW_OK) {
        std::cout << "oi";
        return -1;
    }

    initialize();

    

    float t0 = (float)glfwGetTime();
    while (!glfwWindowShouldClose(win)) {
        float t = (float)glfwGetTime();
        update(t - t0);
        t0 = t+0.1;
        display(win);
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

