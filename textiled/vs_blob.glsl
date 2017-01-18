#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec4 VertexColor;
layout (location = 2) in vec2 VertexTexCoord;

out vec4 Color;
out vec2 TexCoord;
uniform mat4 RotationMatrix;

void main()
{
    TexCoord = VertexTexCoord;
    Color = VertexColor;
    gl_Position = RotationMatrix * vec4(VertexPosition, 1.0);
}