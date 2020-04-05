
#version 330
uniform sampler2D texture0;
uniform float id;
uniform float life;
in vec3 pos;
in vec2 uv;

const vec3 fog = vec3(1.);

void main()
{
    vec3 col = vec3(1., .5+cos(id)*.2, .1)*3.;
    col = mix(col,vec3(.25), 1.f-pow(life,3.));

    float z = (gl_FragCoord.z/gl_FragCoord.w);
    float depth = 1.-exp2(- z*z * 0.00031640425 );
    col = mix( col, fog, min(depth,1.) );

    gl_FragColor = vec4(col, 1.);
}
