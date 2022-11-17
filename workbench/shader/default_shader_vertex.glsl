#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
   gl_Position = vec4(0.05 * aPos.x, 0.05 * aPos.y, 0.05 * aPos.z, 1.0);
}
