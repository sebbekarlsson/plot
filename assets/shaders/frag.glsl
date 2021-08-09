#version 330 core

out vec4 FragColor;
uniform vec4 color;

in vec2 texcoord;
in vec3 colors;

uniform sampler2D imgtexture;


void main()
{
    FragColor = vec4(colors, 1.0) + color;
}
