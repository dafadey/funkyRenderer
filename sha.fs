#version 330

in vec3 normal;
in vec3 color;

layout(location = 0) out vec3 c;
layout(location = 1) out vec3 n;

void main()
{
    c = color;
    n = vec3(normal.x * 0.5 + 0.5, normal.y * 0.5 + 0.5, normal.z * 0.5 + 0.5);
}
