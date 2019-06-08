#version 450 core

layout (location = 3) in vec3 position;
layout (location = 4) in vec3 color;

out vec3 fragcolor;

uniform float currentTime;

void main(void)
{
	float s = sin(currentTime * 10.0f);
	float c = cos(currentTime);
	mat2 rot = mat2(c, s * abs(tan(currentTime)), -s, c);
	vec2 pos = rot * position.xy;
	
	gl_Position = vec4(pos, position.z, 1);
	fragcolor = color;
}