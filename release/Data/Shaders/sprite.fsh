#version 330
in vec2 uv;

uniform sampler2D tex;

uniform vec2 pos;
uniform vec2 size;

void main()
{
    gl_FragColor = texture(tex,uv);
}
