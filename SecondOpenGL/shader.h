#ifndef SHADER_H
#define SHADER_H

#ifdef _WIN32
#include <windows.h>

// Choose glad or glew to initialize OpenGL context on Windows
#include <gl/glew.h>

#include <GLFW/glfw3.h>

#else

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#endif

GLuint CreateShader(GLenum shadertype, const char* filename);
GLuint CreateProgram(int sid, ...);

#endif
