#version 330
uniform sampler2D texture0;

uniform int level;
uniform float id;
in vec2 uv;

void main()
{
    float z = (gl_FragCoord.z/gl_FragCoord.w);
    float depth = 1.-exp2(- z*z * 0.00031640425 );
    vec4 col,fog;
    if(level<=0)
    {
                col = vec4(0.,0.,0., texture(texture0, uv).r);
		fog = vec4(1.,1.,1.,col.a);
    }
    else if(level==1)
    {
		col = vec4( vec3(1., .5+cos(id)*.2, .1), texture(texture0, uv).r*.5);
		fog = vec4(0.,0.,0.,col.a);
    }
    else if(level==2)
    {
                col = vec4(0.,0.,0., texture(texture0, uv).r);
                fog = vec4(vec3(1.),col.a);
    }
    else if(level==3)
    {
                col = vec4( vec3(.1, .5+cos(id)*.2, 1.), texture(texture0, uv).r*.5);
                fog = vec4(1.,1.,1.,col.a);
    }
    gl_FragColor = mix( col, fog, min(depth,1.) );
}
