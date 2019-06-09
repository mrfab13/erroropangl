#version 450 core

in vec3 fragTexCoord;

out vec4 color;
uniform samplerCube cubeSampler;

void main()
{
   color = texture(cubeSampler, fragTexCoord);
}
//#version 450 Core
//in vec3 fragNormal;
//in vec3 fragPos;
//in vec2 fragTexCoord;

//out Vec4 Color;

//uniform vec3 camPos;
//uniform sampler2D Text;
//uniform samplerCube skybox;

//void main()
//{
//    vec3 norm = normalize(fragNormal);
//    vec3 viewDir = normalize(fragPos - camPos);
//    vec3 reflectDir = reflect(viewDir, norm);
//    color = vec4(texture(skybox, reflectDir).rgb, 1.0f);
//}