#version 150

in vec2 v_texcoord;
out vec4 fragColor;

uniform vec2 u_resolution;
uniform sampler2D tex0;

const float near = 0.985;
const float range = .005;

void main() {
    float depth = texture(tex0, v_texcoord).r;
    float b = (depth - near) / range;
    
    fragColor = vec4(vec3(b), 1.0);
}
