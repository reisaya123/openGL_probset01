#version 330 core
layout (location = 0) in vec3 aPos;
in vec4 vertexColor;

out vec4 color; 

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	color = vertexColor;
//	color = vec4(0.5, 0.0, 0.0, 1.0); // output variable to dark-red
}