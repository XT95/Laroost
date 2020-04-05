#version 330
in vec2 uv;

uniform sampler2D tex;
uniform float fade;

void main()
{
    gl_FragColor = vec4(texture(tex, uv).rgb*fade,1.);
}
