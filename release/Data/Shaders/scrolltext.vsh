#version 330

//Input
attribute vec3 position;

uniform vec2 pos;
uniform vec2 offset;
uniform float size;
uniform float time;

out vec2 uv;


void main()
{
    uv = position.xy*vec2(.5,-.5)+.5;
    gl_Position = vec4(position.xy*size*2. + pos + vec2(-time*.1,cos(pos.x*8.+time)*.1), position.z, 1.);
    //gl_Position.y += cos(gl_Position.x)*.25;
}
