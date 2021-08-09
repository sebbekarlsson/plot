#version 330 core

out vec4 FragColor;
uniform vec4 color;

in vec2 texcoord;
in vec3 colors;

uniform sampler2D imgtexture;


void main()
{
    //FragColor = texture(imgtexture, texcoord) * color;

    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(imgtexture, texcoord).r);
    FragColor = color * sampled;
}
