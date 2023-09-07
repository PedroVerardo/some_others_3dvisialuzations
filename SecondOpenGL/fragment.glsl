#version 410

uniform vec4 uniformColor;
out vec4 fcolor;

void main(void)
{
	fcolor = uniformColor;
}
