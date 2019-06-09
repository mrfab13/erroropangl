#version 450 core

in vec3 fragcolor;
in vec2 fragTexCoord;

out vec4 color;

uniform float currentTime;
uniform sampler2D Tex;
uniform sampler2D Tex1;

void main()
{
   // vec3 colortemp = fragcolor * abs(sin(currentTime));
   //color = vec4(colortemp, 1.0f);
   color = mix(texture(Tex1, fragTexCoord), texture(Tex, fragTexCoord), abs(sin(currentTime * 0.01f)));
}