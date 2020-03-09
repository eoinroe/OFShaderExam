#version 410

in vec2 v_texcoord;
out vec4 fragColor;

uniform float threshold;
uniform sampler2D tex0;

// Assumes RGB
// 0.2126*R + 0.7152*G + 0.0722*B
void main() {
    vec3 color = texture(tex0, v_texcoord).rgb;
    float grayscale = dot(color, vec3(0.2126, 0.7152, 0.0722));
    
    fragColor = vec4( vec3(grayscale > threshold ? 1.0f : 0.0), 1.0 );
}
