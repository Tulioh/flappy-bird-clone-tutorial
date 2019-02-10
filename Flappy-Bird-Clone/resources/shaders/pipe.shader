#shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoordinates;

out vec2 v_TexCoord;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);
uniform int top;

void main() {
    gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
    v_TexCoord = textureCoordinates;
    if (top == 1) {
        v_TexCoord.y = 1.0f - v_TexCoord.y;
    }
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main() {
    color = texture(u_Texture, v_TexCoord);
    if (color.w < 1.0f) {
        discard;
    }
}
