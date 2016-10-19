#version 400 core

layout(location=0) in vec4 vPosition;

out VS_OUT
{
    vec4 color;
} vs_out;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void)
{
    gl_Position = proj_matrix*mv_matrix*vPosition;
    vs_out.color = vPosition;
}