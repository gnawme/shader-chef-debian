#version 400
// Fragment shader demonstrating use of uniform block

in vec4 Color;
in vec2 TexCoord;
layout (location = 0) out vec4 FragColor;

uniform sampler2D Sampler;

void main() {
    FragColor = texture(Sampler, TexCoord);
}
