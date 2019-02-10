#shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoordinates;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);
uniform int top;

out Data {
    vec2 texCoord;
    vec3 position;
} vs_out;

void main() {
    gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
    vs_out.texCoord = textureCoordinates;
    vs_out.position = vec3(vw_matrix * ml_matrix * position);
    if (top == 1) {
        vs_out.texCoord.y = 1.0f - vs_out.texCoord.y;
    }
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

in Data
{
    vec2 texCoord;
    vec3 position;
} fs_in;

uniform vec2 bird;
uniform sampler2D u_Texture;

void main() {
    color = texture(u_Texture, fs_in.texCoord);
    if (color.w < 1.0f) {
        discard;
    }
    color *= 2.0 / (length(bird - fs_in.position.xy) + 1.5) + 0.5;
    color.w = 1.0;
}
