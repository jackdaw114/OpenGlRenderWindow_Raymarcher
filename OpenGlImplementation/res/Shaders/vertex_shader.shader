#version 330 core

layout(location = 0) in vec2 position;

out vec2 v_texCoord;

void main()
{
    gl_Position = vec4(position,0,1);
    v_texCoord = clamp(position,0.,1.);

};