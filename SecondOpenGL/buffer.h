#ifndef BUFFER_H
#define BUFFER_H

#ifdef _WIN32
#include <windows.h>

// Choose glad or glew to initialize OpenGL context on Windows
#include <gl/glew.h>

#include <GLFW/glfw3.h>

#else

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#endif

GLuint CreateVAO(void);
void DeleteVAO(GLuint vao);

GLuint CreateBuffer(GLenum target, GLsizeiptr size, const GLvoid* data);
void VertexAttribPointer(GLuint index, GLint size, GLenum type,
    GLboolean norm, GLsizei stride,
    const GLvoid* offset);
void DeleteBuffer(GLuint id);

#endif

