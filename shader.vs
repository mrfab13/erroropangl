#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 fragcolor;
out vec2 fragTexCoord;

uniform float currentTime;


uniform mat4 mvp;


void main(void)
{
	
	gl_Position = mvp * vec4(position, 1.0f) ;

	fragcolor = color;
	fragTexCoord = texCoord;
}