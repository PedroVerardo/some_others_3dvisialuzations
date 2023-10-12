#include "triangle.h"

#include <iostream>

#ifdef _WIN32
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#endif

TrianglePtr Triangle::Make()
{
	return TrianglePtr(new Triangle());
}

Triangle::Triangle()
{
	float coord[] = { -15.0f,-10.0f,15.0f,10.0f,-15.0f,10.0f, 15.0f, -10.0f, -15.0f,-10.0f, 15.0f,10.0f };
	std::vector<glm::vec2> texcoord;
	texcoord.push_back(glm::vec2(0.0f, 1.0f));
	texcoord.push_back(glm::vec2(1.0f, 1.0f));
	texcoord.push_back(glm::vec2( 0.0f, 0.0f));
	texcoord.push_back(glm::vec2(0.0f, 0.0f));
	texcoord.push_back(glm::vec2(1.0f, 1.0f));
	texcoord.push_back(glm::vec2(1.0f, 0.0f));

	// create VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	// create coord buffer
	GLuint id;
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coord), coord, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);  // coord
	glEnableVertexAttribArray(0);

	GLuint texId;
	glGenBuffers(1, &texId);
	glBindBuffer(GL_ARRAY_BUFFER, texId);
	glBufferData(GL_ARRAY_BUFFER, texcoord.size() * sizeof(glm::vec2), &texcoord[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);  // texcoord
	glEnableVertexAttribArray(1);
}

Triangle::~Triangle()
{
}

void Triangle::Draw(StatePtr)
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}