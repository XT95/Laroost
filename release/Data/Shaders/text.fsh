#version 330
in vec2 uv;

uniform sampler2D tex;

uniform vec2 pos;
uniform vec2 offset;
uniform float size;
uniform float time;

void main()
{
    gl_FragColor = vec4(1.,1.,1.,textureLod(tex, uv/16.+offset,0.).r);
}
