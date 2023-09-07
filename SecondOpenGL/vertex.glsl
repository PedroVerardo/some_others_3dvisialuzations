	#version 410

	layout(location = 0) in vec4 vertex;

	uniform mat4 matx;

	void main(void)
	{
		gl_Position = matx*vertex;
	}

