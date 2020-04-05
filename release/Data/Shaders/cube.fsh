
#version 330
uniform sampler2D texture0;
uniform float id;
uniform int level;
in vec3 pos;
in vec2 uv;


void main()
{
    vec3 fog,col;
    if(level <= 0)
    {
        fog = vec3(1.);
        col = texture(texture0, uv).rgb * vec3(1., .5+cos(id)*.2, .1);
        col *= 1.-exp(-(pos.y*.4+.6)*3.); // Fake ao !!
    }
    else if(level == 1)
    {
        fog = vec3(0.);
        col = (vec3(1.)-texture(texture0, uv).rgb)*2. * vec3(1., .5+cos(id)*.2, .1)*2.;
    }
    else if(level == 2)
    {
        fog = vec3(1.);
        col = (1.-texture(texture0, uv).rgb) + vec3(1., .2, .5+cos(id)*.2);
        col *= 1.-exp(-(pos.y*.4+.6)*3.); // Fake ao !!
    }
    else if(level == 3)
    {
        fog = vec3(1.);
        col = (vec3(1.)-texture(texture0, uv).rgb)*2. * vec3(.1, .5+cos(id)*.2, 1.);
    }

    float z = (gl_FragCoord.z/gl_FragCoord.w);
    float depth = 1.-exp2(- z*z * 0.00031640425 );
    col = mix( col, fog, min(depth,1.) );

    gl_FragColor = vec4(col, 1.);
}
