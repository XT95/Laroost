#version 330

//Input
attribute vec3 position;

uniform vec2 pos;
uniform vec2 size;

out vec2 uv;


void main()
{
    uv = position.xy*vec2(.5,-.5)+.5;
    gl_Position = vec4(position*vec3(size,1.)+vec3(pos,0.),1.);
}
