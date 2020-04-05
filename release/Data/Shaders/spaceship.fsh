
#version 330
uniform sampler2D texture0;

in vec3 pos;
in vec2 uv;

const vec3 fog = vec3(1.);

void main()
{
    vec3 col = texture(texture0, uv).rgb;
    col *= (pos.y*.5+.5) * .6 + .4; // Fake ao !!

    float z = (gl_FragCoord.z/gl_FragCoord.w);
    float depth = 1.-exp2(- z*z * 0.00031640425 );
    col = mix( col, fog, min(depth,1.) );

    gl_FragColor = vec4(col, 1.);
}
