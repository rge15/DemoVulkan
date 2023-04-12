#version 450

layout(location = 0) out vec3 fragColor;

layout(push_constant) uniform app_data_t
{
    float   width;
    float   height;
    float   iTime;
    float   rTime;
} data;

void main()
{
    vec2 res = vec2(data.width, data.height);
    vec2 uv = (2.*gl_FragCoord.xy-res.xy)/res.y;

    float duration = 4.;
    float t = min( max( smoothstep(0.,duration,mod(data.rTime,duration)), floor(data.rTime/duration)), 1.);

    float test = mod(data.rTime,duration)/duration;

    float startVal = 2.;
    float endVal   = .1;

    float interVal = t*t*(3.-2.*t);

    endVal *= interVal;
    startVal *= 1.- interVal;

    float lineInit = smoothstep(.1,.0, uv.x - endVal - startVal );
    float lineInit2 = smoothstep(.0,.1, uv.x + endVal + startVal );

    vec3 col = vec3( int(lineInit) & int(lineInit2) );
    
    fragColor = col;
}