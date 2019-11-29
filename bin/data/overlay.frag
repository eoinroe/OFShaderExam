#version 150

in vec2 v_texcoord;
out vec4 fragColor;

uniform vec3 tint;
uniform sampler2D tex0;

vec3 overlay (vec3 src, vec3 dst)
{
    vec3 color = vec3(0.0);

    color.r = dst.x <= 0.5 ? 2.0 * src.x * dst.x
                           : 1.0 - 2.0 * (1.0 - dst.x) * (1.0 - src.x);
    color.g = dst.y <= 0.5 ? 2.0 * src.y * dst.y
                           : 1.0 - 2.0 * (1.0 - dst.y) * (1.0 - src.y);
    color.b = dst.z <= 0.5 ? 2.0 * src.z * dst.z
                           : 1.0 - 2.0 * (1.0 - dst.z) * (1.0 - src.z);

    return color;
}

void main() {
    vec3 color = texture(tex0, v_texcoord).rgb;
    
    // Get grayscale image before applying overlay
    float grayscale = dot(color, vec3(0.2126, 0.7152, 0.0722));
    
    vec3 o = overlay(tint, vec3(grayscale));
    fragColor = vec4(o, 1.0);
}
