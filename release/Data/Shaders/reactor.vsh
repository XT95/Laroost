#version 330
//Input
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord0;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

out vec3 pos;
out vec2 uv;

void main()
{
	pos = position;
	uv = texcoord0;
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position,1.);
}
