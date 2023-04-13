#version 450

layout(location = 0) out vec3 fragColor;

layout(push_constant) uniform app_data_t
{
    float   width;
    float   height;
    float   iTime;
    float   rTime;
} data;

#define PI 3.14159265


float N21(in vec2 p)
{
    p = 50.*fract( p * PI);
    p = 50.*fract((p+vec2(0.24342,709.23))/PI);

    return -1. + 2.*fract((p.x*p.y));
}

vec2 modulo(in vec2 divident, in vec2 divisor)
{
   return mod(divident,divisor) * (divisor / abs(divisor));
}

float tiledValueNoise(in vec2 uv, float freq)
{
    vec2 f = fract(uv);

    vec2 imin = floor(uv);
    vec2 imax = ceil(uv);
 
    imin = modulo( imin, vec2(freq) );
    imax = modulo( imax, vec2(freq) ); 

    vec2 func = f*f*(3.-2.*f);

    float a = N21(imin);
    float b = N21(vec2(imax.x,imin.y));
    float c = N21(vec2(imin.x,imax.y));
    float d = N21(imax);
    
    return a + (b-a) * func.x + (c-a) * func.y + (d-b-c+a) * func.x * func.y;
}


void main()
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 res = vec2(data.width, data.height);
    vec2 uv = (2.*gl_FragCoord.xy-res.xy)/res.y;
    
    //float dist = sin(iTime)/length(uv);
    float dist = 0.03/length(uv);
    
    //float dist = 1./length(uv)+iTime*0.5;
    float shade = length(uv);

    float angle = atan(uv.x,uv.y)/PI;
    
    vec3 col = vec3(dist,angle,shade);
    
    float noise1 = tiledValueNoise(vec2(dist,angle)*20.,40.);
    float noise2 = tiledValueNoise(vec2(noise1+data.rTime,angle)*2.,2.);

    float noise = tiledValueNoise(uv*8.,100.);

    vec3 final = vec3(sin(noise2)*cos(data.rTime),cos(noise2)*sin(data.rTime), tan(noise1)*sin(data.rTime)) * shade + 0.5;

    // Output to screen
    fragColor = final;
}