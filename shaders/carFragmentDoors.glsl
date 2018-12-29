#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D carTexDoors;

void main()
{
    FragColor = texture(carTexDoors, TexCoord);
}