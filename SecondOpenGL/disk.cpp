#include "disk.h"

#include <iostream>

#ifdef _WIN32
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#endif

#define M_PI 0x3F
const int definition = 100;

DiskPtr Disk::Make()
{
	return DiskPtr(new Disk());
}

Disk::Disk()
{
	float r = 0.5f;
	float x = 0.0f;
	float y = 0.0f;

	float circleVertices[definition * 2];
	for (int i = 0; i < definition; ++i) {
		float dgree = 2.0 * M_PI * float(i) / float(definition);
		circleVertices[i * 2] = (r * cos(dgree) + x) / 2;
		circleVertices[i * 2 + 1] = (r * sin(dgree) + y) / 2;
	}
	// create VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	// create coord buffer
	GLuint id;
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);  // coord
	glEnableVertexAttribArray(0);
}

Disk::~Disk()
{
}

void Disk::Draw(StatePtr)
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, definition);
}