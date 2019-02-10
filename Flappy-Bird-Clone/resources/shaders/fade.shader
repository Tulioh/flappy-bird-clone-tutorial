#shader vertex
#version 330 core

void main() {
    const vec4 vertices[6] = vec4[6](vec4( 1.0, -1.0, -0.5, 1.0),
                                     vec4(-1.0, -1.0, -0.5, 1.0),
                                     vec4( 1.0,  1.0, -0.5, 1.0),
                                     vec4( 1.0,  1.0, -0.5, 1.0),
                                     vec4(-1.0, -1.0, -0.5, 1.0),
                                     vec4(-1.0,  1.0, -0.5, 1.0));
    gl_Position = vertices[gl_VertexID];
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

uniform float time;

void main()
{
    if (time > 1.0) {
        discard;
    }
    x`xcolor = vec4(1.0, 1.0, 1.0, 1.0 - time);
}
