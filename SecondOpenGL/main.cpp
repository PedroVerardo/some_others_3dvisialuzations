
#ifdef _WIN32
#include <gl/glew.h>
#else
#include <OpenGL/gl3.h>
#endif
#include <GLFW/glfw3.h>
#include "glm/gtc/type_ptr.hpp" 
#include "arcball.h"
#include "scene.h"
#include "state.h"
#include "camera3d.h"
#include "material.h"
#include "texture.h"
#include "transform.h"
#include "skybox.h"
#include "cube.h"
#include "quad.h"
#include "sphere.h"
#include "error.h"
#include "shader.h"
#include "light.h"
#include "light.h"
#include "texcube.h"
#include "variable.h"
#include "polyoffset.h"

#include <iostream>

static float viewer_pos[3] = { 2.0f, 3.5f, 4.0f };

static ScenePtr scene;
static Camera3DPtr camera;
static ArcballPtr arcball;
static SkyBoxPtr box;

static void initialize(void)
{
    // set background color: white 
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // enable depth test 
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);  // cull back faces

    // create objects
    camera = Camera3D::Make(viewer_pos[0], viewer_pos[1], viewer_pos[2]);
    //camera->SetOrtho(true);
    arcball = camera->CreateArcball();
    //create a skybox
     
    //LightPtr light = ObjLight::Make(viewer_pos[0],viewer_pos[1],viewer_pos[2]);
    LightPtr light = Light::Make(0.0f, 0.0f, 0.0f, 1.0f, "camera");
    //LightPtr light_lamp = Light::Make(-1.5f, 1.7f, 0.0f, 1.0f, "camera");

    AppearancePtr white = Material::Make(1.0f, 1.0f, 1.0f);
    AppearancePtr red = Material::Make(1.0f, 0.5f, 0.5f);
    AppearancePtr red2 = Material::Make(1.0f, 0.0f, 0.0f);
    AppearancePtr green = Material::Make(0.0f, 1.0f, 0.0f);
    AppearancePtr blue = Material::Make(0.0f, 0.0f, 1.0f);
    AppearancePtr yellow = Material::Make(1.0f, 1.0f, 0.2f);
    AppearancePtr poff = PolygonOffset::Make(-1, 1);
    //AppearancePtr metal = Texture::Make("decal", "C:\\Users\\Pedro\\source\\repos\\SecondOpenGL\\SecondOpenGL\\images\\metal2.jpg");
    AppearancePtr wood = Texture::Make("decal", "C:\\Users\\Pedro\\source\\repos\\SecondOpenGL\\SecondOpenGL\\images\\wood.jpg");
    AppearancePtr slide = Texture::Make("decal", "C:\\Users\\Pedro\\source\\repos\\SecondOpenGL\\SecondOpenGL\\images\\smile_face.jpg");
    AppearancePtr sky = TexCube::Make("sky", "C:\\Users\\Pedro\\source\\repos\\SecondOpenGL\\SecondOpenGL\\images\\skybox.jpg");
    //AppearancePtr earth = Texture::Make("decal", "C:\\Users\\Pedro\\source\\repos\\SecondOpenGL\\SecondOpenGL\\images\\earth.jpg");
    //AppearancePtr earthNorm = Texture::Make("normalMap", "C:\\Users\\Pedro\\source\\repos\\SecondOpenGL\\SecondOpenGL\\images\\earth.jpg");

    //table
    TransformPtr trf0 = Transform::Make();
    trf0->Translate(1.8f, 1.8f, 0.0f);

    TransformPtr trf1 = Transform::Make();
    trf1->Scale(200.0f, 0.3f, 200.0f);
    trf1->Translate(0.0f, -5.0f, 0.0f);
    //paper
    TransformPtr trf3 = Transform::Make();
    trf3->Translate(40.f, 0.0f, 0.8f);
    //trf3->Scale(10.f, 0.7f, 1.0f);
    //ball blue
    TransformPtr trf4 = Transform::Make();
    trf4->Translate(80.f, 0.1f, 8.f);
    //trf4->Scale(20.f, 0.1f, 0.1f);
    //green ball
    TransformPtr trf5 = Transform::Make();
    trf5->Translate(0.0f, 0.1f, 0.0f);
    trf5->Scale(160.f, 0.1f, 0.1f);
    //white ball
    TransformPtr trf14 = Transform::Make();
    trf14->Translate(-0.3f, 0.1f, -0.3f);
    trf14->Scale(0.1f, 0.1f, 0.1f);
    //table leg 1
    TransformPtr trf6 = Transform::Make();
    trf6->Scale(0.5f, 2.5f, 0.5f);
    trf6->Translate(-2.5f, -1.0f, -2.5f);
    //table leg 2
    TransformPtr trf7 = Transform::Make();
    trf7->Scale(0.5f, 2.5f, 0.5f);
    trf7->Translate(2.5f, -1.0f, 2.5f);
    //table leg 3
    TransformPtr trf8 = Transform::Make();
    trf8->Scale(0.5f, 2.5f, 0.5f);
    trf8->Translate(-2.5f, -1.0f, 2.5f);
    // table leg 4
    TransformPtr trf9 = Transform::Make();
    trf9->Scale(0.5f, 2.5f, 0.5f);
    trf9->Translate(2.5f, -1.0f, -2.5f);
    // lighting base
    TransformPtr trf2 = Transform::Make();
    //trf2->Scale(0.7f, 0.02f, 0.7f);
    // lighting suport 1
    TransformPtr trf10 = Transform::Make();
    trf10->Rotate(10.0f, 0.0f, 0.0f, 1.0f);
    trf10->Scale(0.1f, 2.0f, 0.1f);
    trf9->Translate(30.f, -1.0f, 4.f);
    // lighting suport 2
    TransformPtr trf11 = Transform::Make();
    trf11->Rotate(30.0f, 0.0f, 0.0f, 1.0f);
    trf11->Scale(0.1f, 2.0f, 0.1f);
    // suport 3
    TransformPtr trf12 = Transform::Make();
    trf12->Translate(0.0f, 1.5f, 0.0f);
    trf12->Rotate(75.0f, 0.0f, 0.0f, 1.0f);
    trf12->Scale(0.1f, 1.5f, 0.1f);
    // lighting lamp 
    TransformPtr trf13 = Transform::Make();
    trf13->Translate(-1.5f, 1.7f, 0.0f);
    trf13->Scale(0.2f, 0.2f, 0.2f);

    Error::Check("before shps");
    ShapePtr cube = Cube::Make();
    Error::Check("before quad");
    ShapePtr quad = Quad::Make();
    Error::Check("before sphere");
    ShapePtr sphere = Sphere::Make();
    Error::Check("after shps");
    ShapePtr skybox = SkyBox::Make();
    Error::Check("after skybox");

    // create shader
    //ShaderPtr shader = Shader::Make();
    //shader->AttachVertexShader("shader/ilum_vert/vertex.glsl");
    //shader->AttachFragmentShader("shader/ilum_vert/fragment.glsl");
    //shader->Link();
    ShaderPtr shader = Shader::Make(light, "world");
    shader->AttachVertexShader("./shaders/fog_shader/vertex.txt");
    shader->AttachFragmentShader("./shaders/fog_shader/fragment.txt");
    shader->Link();

    ShaderPtr shd_env = Shader::Make(light, "world");
    shd_env -> AttachVertexShader("C:\\Users\\Pedro\\source\\repos\\SecondOpenGL\\SecondOpenGL\\shaders\\shade_env\\vertex.txt");
    shd_env -> AttachFragmentShader("C:\\Users\\Pedro\\source\\repos\\SecondOpenGL\\SecondOpenGL\\shaders\\shade_env\\fragment.txt");
    shd_env -> Link();
        
    ShaderPtr shd_sky = Shader::Make();
    shd_sky -> AttachVertexShader("C:\\Users\\Pedro\\source\\repos\\SecondOpenGL\\SecondOpenGL\\shaders\\skybox\\vertex.txt");
    shd_sky -> AttachFragmentShader("C:\\Users\\Pedro\\source\\repos\\SecondOpenGL\\SecondOpenGL\\shaders\\skybox\\fragment.txt");
    shd_sky -> Link();

    /*ShaderPtr shd_rugos_tex = Shader::Make(light, "world");
    shd_sky->AttachVertexShader("C:\\Users\\Pedro\\source\\repos\\SecondOpenGL\\SecondOpenGL\\shaders\\rugosidade\\vertex.txt");
    shd_sky->AttachFragmentShader("C:\\Users\\Pedro\\source\\repos\\SecondOpenGL\\SecondOpenGL\\shaders\\rugosidade\\fragment.txt");
    shd_sky->Link();*/

    /*ShaderPtr shd_tex = Shader::Make(light, "world");
    shd_tex->AttachVertexShader("./shaders/texture/vertex.glsl");
    shd_tex->AttachFragmentShader("./shaders/texture/fragment.glsl");
    shd_tex->Link();*/

    glm::mat4 translate = glm::translate(glm::mat4 (1.0f),
        glm::vec3 (0.5f,0.5f,0.5f));
    glm::mat4 scale = glm::scale(glm::mat4 (1.0f), glm::vec3 (0.5f, 0.5f, 0.5f));
    glm::mat4 modelview = camera -> GetProjMatrix()*camera -> GetViewMatrix();
    glm::mat4 mat = translate * scale * modelview;
    auto mtex = Variable<glm::mat4>::Make("Mtex", mat);

    auto fcolor = Variable<glm::vec4>::Make("fcolor",
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
    );

    auto fdensity = Variable<float>::Make("fdensity", 0.25f);

    // build scene
    NodePtr root = Node::Make(shader,{ fcolor , fdensity},
        { 
            Node::Make(shd_env,{white,sky},{
                Node::Make(shd_sky,{sky},{skybox}),
                Node::Make({sphere})}),
            Node::Make(trf1,{red, wood},{cube}),
            //Node::Make(trf2,{blue},{cube}),
            Node::Make(trf3,{blue, wood},{cube}),
            Node::Make(trf4,{blue, wood},{cube}),
            Node::Make(trf5,{blue, wood},{cube}),
            //Node::Make(shd_rugos_tex, trf0, {sphere}),
            
            //render all table
            //,poff,wood
            //Node::Make( trf1,{red},{cube}),
            //Node::Make( trf6,{red},{cube}),
            //Node::Make( trf7,{red},{cube}),
            //Node::Make( trf8,{red},{cube}),
            //Node::Make( trf9,{red},{cube}),
            ////render some balls
            //Node::Make(trf4,{blue},{sphere}),
            //Node::Make(trf5,{green},{sphere}),
            //Node::Make(trf14,{red2},{sphere}),
            ////lighting
            //Node::Make(trf0,{
            //    Node::Make(trf2,{white},{sphere}),
            //    Node::Make(trf10,{white},{cube}),
            //    Node::Make(trf11,{white},{cube}),
            //    Node::Make(trf12,{white},{cube}),
            //    Node::Make(trf13,{yellow},{sphere})
            //})
            //Node::Make(shd_tex,trf3,{white,poff,paper},{quad}),
        }
    );
    scene = Scene::Make(root);
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

static void cursorpos(GLFWwindow* win, double x, double y)
{
    // convert screen pos (upside down) to framebuffer pos (e.g., retina displays)
    int wn_w, wn_h, fb_w, fb_h;
    glfwGetWindowSize(win, &wn_w, &wn_h);
    glfwGetFramebufferSize(win, &fb_w, &fb_h);
    x = x * fb_w / wn_w;
    y = (wn_h - y) * fb_h / wn_h;
    arcball->AccumulateMouseMotion(x, y);
}
static void cursorinit(GLFWwindow* win, double x, double y)
{
    // convert screen pos (upside down) to framebuffer pos (e.g., retina displays)
    int wn_w, wn_h, fb_w, fb_h;
    glfwGetWindowSize(win, &wn_w, &wn_h);
    glfwGetFramebufferSize(win, &fb_w, &fb_h);
    x = x * fb_w / wn_w;
    y = (wn_h - y) * fb_h / wn_h;
    arcball->InitMouseMotion(x, y);
    glfwSetCursorPosCallback(win, cursorpos);     // cursor position callback
}
static void mousebutton(GLFWwindow* win, int button, int action, int mods)
{
    if (action == GLFW_PRESS) {
        glfwSetCursorPosCallback(win, cursorinit);     // cursor position callback
    }
    else // GLFW_RELEASE 
        glfwSetCursorPosCallback(win, nullptr);      // callback disabled
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);       // required for mac os
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);  // option for mac os

    glfwSetErrorCallback(error);

    GLFWwindow* win = glfwCreateWindow(600, 400, "Window title", nullptr, nullptr);
    glfwSetFramebufferSizeCallback(win, resize);  // resize callback
    glfwSetKeyCallback(win, keyboard);            // keyboard callback
    glfwSetMouseButtonCallback(win, mousebutton); // mouse button callback

    glfwMakeContextCurrent(win);
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    if (glewInit() != GLEW_OK) {
        return 0;
    }

    initialize();

    while (!glfwWindowShouldClose(win)) {
        display(win);
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

