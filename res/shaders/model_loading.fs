#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

vec4 colorTex;
vec4 color;
vec4 x;

void main()
{    
    /* //Great!!    
    vec4 colorito = vec4(0.5, 0.5, 0.5, 0.5);
    colorTex = texture(texture_diffuse1, TexCoords);
    color = mix(colorito, colorTex, 0.8);
    FragColor = color; */

    FragColor = texture(texture_diffuse1, TexCoords);
}