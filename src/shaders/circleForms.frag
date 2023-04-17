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
#define PERIOD 27.0
#define TIMESTEP 3.


float timeMark( in float timeDuration, in float timeStart )
{
    float t = step(0.,data.rTime-timeStart) * max( smoothstep(0.,timeDuration,mod(data.rTime-timeStart,timeDuration)), step(0.,data.rTime-timeStart-timeDuration));

    return  t;
}

float periodicTimeMark( in float timeDuration, in float timeStart )
{
    float time = mod(data.rTime, PERIOD);
    float t = step(0.,time-timeStart) * max( smoothstep(0.,timeDuration,mod(time-timeStart,timeDuration)), step(0.,time-timeStart-timeDuration));

    return  t;
}


float invPeriodicTimeMark( in float timeDuration, in float timeStart )
{
    return 1.- periodicTimeMark(timeDuration, timeStart);
}

float mask1(in vec2 uv)
{
    float x = uv.x-data.rTime;
    float y = uv.y;

    float oriFunc = mod(x*0.25+pow(y,0.5),0.5);
    float subFunc = mod(-0.05+x*0.25+pow(y,0.5),0.5);

    float oriF = smoothstep(0.61,0.6,(oriFunc + y));
    float subF = smoothstep(0.5,0.51,(subFunc + y));

    float f = float(int(oriF) & int(subF));

    return f;
}

float mask1Inv(in vec2 uv)
{
    float invX = -1.*uv.x-data.rTime*2.;
    float y = uv.y;

    float invOriFunc = mod(invX*0.25+pow(y,0.5),0.5);
    float invSubFunc = mod(-0.05+invX*0.25+pow(y,0.5),0.5);

    float invOriF = smoothstep(0.61,0.6,(invOriFunc + y));
    float invSubF = smoothstep(0.5,0.51,(invSubFunc + y));

    float invF = float(int(invOriF) & int(invSubF));

    return invF;
}

float mask2(in vec2 uv)
{
    float x = uv.x;
    float y = uv.y;
    
    float Func = mod(x+sin(y*1.5*PI)+data.rTime,.5);

    float f = smoothstep(0.51,0.5,Func+y);

    return f;
}

float mask2Inv(in vec2 uv)
{
    float invX = -uv.x;
    float y = uv.y;
    
    float invFunc = mod(invX+sin(y*1.5*PI)+data.rTime,.5);
    
    float invF = smoothstep(0.51,0.5,invFunc+y);
    
    return invF;
}

int moonsMask(vec2 uv)
{
    float C11 = length(uv-vec2(0.4,0.))-0.4;
    float F11 = smoothstep(0.,0.01, C11);
    float C12 = length(uv-vec2(0.5,0.))-0.3;
    float F12 = smoothstep(0.,0.01, C12);
    float C21 = length(uv-vec2(-0.4,0.))-0.4;
    float F21 = smoothstep(0.,0.01, C21);    
    float C22 = length(uv-vec2(-0.5,0.))-0.3;
    float F22 = smoothstep(0.,0.01, C22);
    int F1 = int(F11) ^ int(F12);
    int F2 = int(F21) ^ int(F22);    
    
    float center = length(uv)-0.1;
    float cen = smoothstep(0.01,0.0,center);
    
    return F1+F2-int(cen);
}

vec2 shapeSelect(in vec2 p_polarUV, in vec2 p_uv )
{
    float t1M = invPeriodicTimeMark(0.01, TIMESTEP*3);
    float t2M = invPeriodicTimeMark(0.01, TIMESTEP*4);

    float t1 = periodicTimeMark( 0.01, TIMESTEP   ) * int(t1M);
    float t2 = periodicTimeMark( 0.01, TIMESTEP*2 ) * int(t2M);
    float t3 = int(periodicTimeMark( 0.01, TIMESTEP*5)) * 2;
    float t4 = periodicTimeMark( 0.01, TIMESTEP*6 ) * -1;
    float t5 = periodicTimeMark( 0.01, TIMESTEP*7 ) * -1;
    float t6 = int(periodicTimeMark( 0.01, TIMESTEP*8)) * 2;

    int shapeSelect = int(t1) + int(t2) + int(t3) + int(t4) + int(t5) + int(t6);
    vec2 shape = vec2(0.); 
    if( shapeSelect == 0 )
    {
        shape.x = mask1(p_polarUV);
        shape.y = mask1Inv(p_polarUV);
    }else if( shapeSelect == 1 )
    {
        shape.x = mask2(p_polarUV);
        shape.y = mask2Inv(p_polarUV);
    }else if( shapeSelect == 2 )
    {
        float deg1 = data.rTime*1.5;
        float deg2 = -data.rTime*1.5;

        mat2 rotM1 = mat2( cos(deg1), -sin(deg1), sin(deg1), cos(deg1));
        mat2 rotM2 = mat2( cos(deg2), -sin(deg2), sin(deg2), cos(deg2));

        vec2 uv1 = p_uv * rotM1;
        vec2 uv2 = p_uv * rotM2;
        shape.x = moonsMask(uv1);
        shape.y = moonsMask(uv2);
    }

    return shape;
}

float maskSelect(in vec2 p_shape)
{
    float t1 = periodicTimeMark(0.01, TIMESTEP * 3 );
    float t2 = periodicTimeMark(0.01, TIMESTEP * 4 );
    float t3 = periodicTimeMark(0.01, TIMESTEP * 5 );// Negative
    float t4 = periodicTimeMark(0.01, TIMESTEP * 6 );
    float t5 = periodicTimeMark(0.01, TIMESTEP * 7 );// Negative
    float t6 = periodicTimeMark(0.01, TIMESTEP * 8 );

    int maskSelect = int(t1)+int(t2)-int(t3)+int(t4)-int(t5)+int(t6);

    int final = 0;
    if( maskSelect == 0 )
    {
        final = int(p_shape.x) | int(p_shape.y);
    }else if( maskSelect == 1 )
    {
        final = int(p_shape.x) ^ int(p_shape.y);
    }else if( maskSelect == 2 )
    {
        final = int(p_shape.x) & int(p_shape.y);
    }

    return float(final);
}

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

float tunnelMask( in vec2 p_uv )
{
    float dist = 1./length(p_uv)+data.rTime*0.5;
    float angle = atan(p_uv.x,p_uv.y)/PI;
    
    float shadeIntensity = timeMark( 10., 44.) * 10.;
    float shadeSize      = 1. - timeMark( 5., 50.);

    float shade = clamp(0.,1., 1. - length(p_uv*shadeSize) );
    
    float noise1 = tiledValueNoise(vec2(dist,angle)*20.,40.);
    float noise2 = tiledValueNoise(vec2(noise1+data.rTime,angle)*2.,2.);

    float noise = tiledValueNoise(p_uv*8.,100.);

    float f1 = sin(noise2)*cos(data.rTime);
    float f2 = sin(noise2)*sin(data.rTime);
    float f3 = tan(noise1)*sin(data.rTime);
    
    float f = f1+f2+f3 + shadeIntensity * shade;
    
    return f;
}

void main()
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 res = vec2(data.width, data.height);
    vec2 uv    = (2.*gl_FragCoord.xy-res.xy)/res.y;
    vec2 p_uv  = vec2( atan(uv.x,uv.y) , length(uv));
    vec2 np_uv = vec2( p_uv.x/PI*2.+0.5 , p_uv.y);
    vec2 uvValue = np_uv;

    vec2 shape = shapeSelect(uvValue, uv);
    
    float final = step(0.1,maskSelect(shape));

    float tunnelMaskTransition = timeMark(4., 25.);
    
    if(tunnelMaskTransition != 0)
    {
        float tunMask = clamp(0.,1., ( tunnelMask( uv ) * tunnelMaskTransition ) );
        final *= 2.;
        final += tunMask;
    }
    
    float endPoint = 1. - timeMark( 0.01, 54. );

    // Time varying pixel color
    vec3 col = vec3(final) * endPoint;

    // Output to screen
    fragColor = col;
}