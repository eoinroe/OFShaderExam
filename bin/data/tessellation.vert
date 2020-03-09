#version 410 core

in vec4 position;
in vec3 normal;
in vec2 texcoord;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexcoord;

void main() {
    vTexcoord = texcoord;
    vNormal = normal;
    vPosition = position.xyz;
}
