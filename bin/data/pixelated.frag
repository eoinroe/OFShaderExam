#version 150

in vec2 v_texcoord;
out vec4 fragColor;

uniform vec2 u_resolution;
uniform sampler2D tex0;

void main() {
    vec2 lod = u_resolution / 16.0;
    vec2 uv = v_texcoord;
    
    uv = floor(uv * lod) / lod;
    
    vec3 color = texture(tex0, uv).rgb;
    fragColor = vec4(color, 1.0);
}
