#version 330
uniform int level;
uniform float speed, time;
uniform sampler2D texture0;
in vec2 uv;

void main()
{
    vec3 col,fog;
    if(level<=0)
    {
        col = vec3(.5);
    	fog = vec3(1.);
    }
    else if(level==1)
    {
        fog = vec3(0.);
        col = vec3(.1);
    }
    else if(level==2)
    {
        fog = vec3(1.);
        col = vec3(.6,1.,.5)*.5;
    }
    else if(level==3)
    {
        fog = vec3(1.);
        col = vec3(.8,1.,1.)*.1;
    }
    float z = (gl_FragCoord.z/gl_FragCoord.w);
    float depth = 1.-exp2(- z*z * 0.00031640425 );
    col = mix( col, fog, min(depth,1.) );


    gl_FragColor = vec4(col, 1.);
}
