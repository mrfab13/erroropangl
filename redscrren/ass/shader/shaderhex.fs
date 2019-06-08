#version 450 core

in vec3 fragcolor;

out vec4 color;

uniform float currentTime;

void main()
{
    vec3 colortemp = fragcolor * abs(sin(currentTime));
    color = vec4(colortemp, 1.0f);
}