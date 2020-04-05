#version 330
in vec2 uv;

uniform sampler2D tex;

void main()
{
    vec3 col;
    vec2 offset = vec2( length(uv-vec2(.5))/300.);
    col.r = texture(tex, uv-offset).r;
    col.g = texture(tex, uv).g;
    col.b = texture(tex, uv+offset).b;

    //Vignetting
    col *= 0.5 + 0.5*pow(16.0*uv.x*uv.y*(1.0-uv.x)*(1.0-uv.y),0.2);

    //Gamma correction
    //col = pow( col, vec3(1./2.2) );

    gl_FragColor = vec4(min(col,vec3(1.)),1.);
}
