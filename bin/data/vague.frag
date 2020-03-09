#version 410

in vec2 v_texcoord;
out vec4 fragColor;

uniform float level;
uniform vec2 u_resolution;
uniform sampler2D tex0;

void main() {
    vec2 uv = v_texcoord;
    //uv.x += sin(uv.y * 50.0) * 0.03;
    //uv.x += sin(uv.y * 50.0) * level;
    uv.x += sin(uv.y * level * 500.0f) * 0.03;
            
    vec3 color = texture(tex0, uv).rgb;
    fragColor = vec4(color, 1.0);
}
