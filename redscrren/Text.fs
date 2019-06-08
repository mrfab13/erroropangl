#version 450 core 

in vec2 fragTexCoord;

out vec4 color;

uniform sampler2D tex;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(tex, fragTexCoord).r);
    color = vec4(textColor, 1.0f) * sampled;
}