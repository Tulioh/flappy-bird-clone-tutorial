#shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoordinates;

uniform mat4 pr_matrix;

void main() {
    gl_Position = pr_matrix * position;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

void main() {
    color = vec4(0.2f, 0.3f, 0.8f, 1.0);
}
