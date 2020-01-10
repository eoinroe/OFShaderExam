#version 150

in vec2 v_texcoord;
out vec4 fragColor;

uniform vec2 u_resolution;
uniform sampler2D tex0;

void main() {
    float scale = 0.0025;
    float a = 0.0;
    
    vec2 uv = v_texcoord;
    
    vec2 uvR = vec2(cos(a), sin(a)) * scale;
    a += 3.14159;
    
    vec2 uvG = vec2(cos(a), sin(a)) * scale;
    a += 3.14159;
    
    vec2 uvB = vec2(cos(a), sin(a)) * scale;
    
    vec3 color = vec3(0.0);
    color.r = texture(tex0, uv+uvR).r;
    color.g = texture(tex0, uv+uvG).g;
    color.b = texture(tex0, uv+uvB).b;
    
    fragColor = vec4(color, 1.0);
}
