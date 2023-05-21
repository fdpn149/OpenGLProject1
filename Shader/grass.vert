#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in int aType;

out int type;

void main()
{
	gl_Position = vec4(aPos, 1.0f) ;

	type = aType;
}
