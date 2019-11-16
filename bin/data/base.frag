#version 150

in vec2 v_texcoord;
out vec4 fragColor;

uniform sampler2D tex0;

void main() {
    vec3 color = texture(tex0, v_texcoord).rgb;
    fragColor = vec4(color, 1.0);
}
