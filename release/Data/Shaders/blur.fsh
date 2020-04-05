#version 330
in vec2 uv;

uniform sampler2D tex;
uniform vec2 offset;

void main()
{
	vec3 col = texture(tex, uv).rgb;
	for(int i=1; i<10; i++)
		col += texture(tex, uv+offset*i).rgb;
    col /= 20.;
    //Vignetting
    col *= 0.5 + 0.5*pow(16.0*uv.x*uv.y*(1.0-uv.x)*(1.0-uv.y),0.2);

    gl_FragColor = vec4(col, 1.);
}
