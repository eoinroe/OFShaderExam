#version 150

in vec4 position;
in vec3 normal;
in vec2 texcoord;

out vec2 v_texcoord;

uniform float size;
uniform float twistFactor;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

mat4 rotationAroundY(float angle) {
    return mat4(cos(angle), 0.0, -sin(angle), 0.0,
                0.0,        1.0,  0.0,        0.0,
                sin(angle), 0.0,  cos(angle), 0.0,
                0.0,        0.0,  0.0,        1.0);
}

void main() {
    v_texcoord = texcoord;
    
    float rotationAngleY = position.y * twistFactor;
    vec4 pos = position * rotationAroundY(rotationAngleY);
    //vec4 worldSpacePos = modelMatrix * pos;
    
    vec4 worldSpacePos = pos * transpose(modelMatrix);
    
    // Inflate the model
    worldSpacePos.xyz += normal * size;
    
    gl_Position = projectionMatrix * viewMatrix * worldSpacePos;
}
