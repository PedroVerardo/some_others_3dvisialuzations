#include "disk.h"

#include <iostream>

#ifdef _WIN32
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#endif

#define M_PI 0x3F
const int definition = 900;

DiskPtr Disk::Make()
{
	return DiskPtr(new Disk());
}

Disk::Disk()
{
    std::vector<glm::vec2> texcoord;
	texcoord.push_back(glm::vec2(0.5f, 0.5f));

	float r = 0.5f;
	float x = 0.0f;
	float y = 0.0f;
	float temp1;
	float temp2;

	float circleVertices[definition * 2];
	for (int i = 0; i < definition; ++i) {
		float dgree = 2.0 * M_PI * float(i) / float(definition);
		temp1 = (r * cos(dgree) + x) / 2;
		temp2 = (r * sin(dgree) + y) / 2;
		circleVertices[i * 2] = temp1;
		circleVertices[i * 2 + 1] = temp2;

		texcoord.push_back(glm::vec2(temp1, temp2));
		texcoord.push_back(glm::vec2(temp1, temp2));
		texcoord.push_back(glm::vec2(temp1, temp2));
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

	GLuint texId;
	glGenBuffers(1, &texId);
	glBindBuffer(GL_ARRAY_BUFFER, texId);
	glBufferData(GL_ARRAY_BUFFER, texcoord.size() * sizeof(glm::vec2), &texcoord[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);  // texcoord
	glEnableVertexAttribArray(1);
}

Disk::~Disk()
{
}

void Disk::Draw(StatePtr)
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, definition);
}