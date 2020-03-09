#version 410

in vec2 v_texcoord;
out vec4 fragColor;

uniform float level;
//uniform vec2 lod;
uniform vec2 u_resolution;
uniform sampler2D tex0;

float random(vec2 st) {
    return fract( sin( dot(st.xy, vec2(12.9898, 78.233)) ) * 43758.5453123 );
}

void main() {
    vec2 lod = u_resolution * 4.0;
    vec2 uv = v_texcoord;
    
    uv += ( random(floor(uv * lod) / lod) * 2.0 - 1.0 ) * level;
    
    vec3 color = texture(tex0, uv).rgb;
    fragColor = vec4(color, 1.0);
}
