#version 330
in vec2 uv;
uniform int level;
uniform float offset;

vec2 rotate(vec2 v, float a)
{
    return vec2( v.x*cos(a) - v.y*sin(a), v.x*sin(a) + v.y*cos(a) );
}

void main()
{
    vec2 v = rotate( uv, offset*30.5 );
    if(level <= 0 || level == 2)
        gl_FragColor = vec4( mix( vec3(1.), vec3(.1, .7, 1.), v.y), 1.);
    else if(level == 1)
         gl_FragColor = vec4(0.,0.,0., 1.);
    else if(level == 3)
    {
        gl_FragColor = vec4( mix( vec3(1.), vec3(1., .3, 1.), v.y), 1.);
    }
}
