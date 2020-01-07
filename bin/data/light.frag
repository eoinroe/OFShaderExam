#version 150

in vec2 v_texcoord;
in vec3 v_normal;

out vec4 fragColor;

uniform sampler2D tex0;

void main() {
    vec3 color = texture(tex0, v_texcoord).rgb;
    
    // Directional light
    vec3 lightDirection = vec3(1.0, 1.0, -3.0);
    
    // The light intensity is proportional to the angle between the incoming light and the surface normal
    //float intensity = dot(normalize(v_normal), normalize(lightDirection));
    
    // Assuming the light color is vec4(1.0)
    //fragColor = vec4(max(vec3(0.0), color * intensity), 1.0);
    
    // Can also clamp the values like this and vary the light color
    float intensity = max(0.0, dot(normalize(v_normal), normalize(lightDirection)));
    fragColor = vec4(color * intensity * vec3(0.75), 1.0);
    
    // Change light color rather than overlay color?
}
