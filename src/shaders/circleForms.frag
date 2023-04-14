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

float timeMark( in float timeDuration, in float timeStart )
{
    float t = step(0.,data.rTime-timeStart) * max( smoothstep(0.,timeDuration,mod(data.rTime-timeStart,timeDuration)), step(0.,data.rTime-timeStart-timeDuration));

    return  t;
}

float invTimeMark( in float timeDuration, in float timeStart )
{
    return 1.- timeMark(timeDuration, timeStart);
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

float invMask2(in vec2 uv)
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

void main()
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 res = vec2(data.width, data.height);
    vec2 uv    = (2.*gl_FragCoord.xy-res.xy)/res.y;
    vec2 p_uv  = vec2( atan(uv.x,uv.y) , length(uv));
    vec2 np_uv = vec2( p_uv.x/PI*2.+0.5 , p_uv.y);

    vec2 uvValue = np_uv;

    //TODO : Aquí hacer un select de valor en base al tiempo 
    float f1 = mask1(uvValue);
    float f1Inv = mask1Inv(uvValue);

    //float f1 = mask2(uvValue);
    //float f1Inv = mask2Inv(uvValue);

    //mat2 rotM1 = mat2( cos(deg1),-sin(deg1),sin(deg1),cos(deg1) );
    //mat2 rotM2 = mat2( cos(deg2),-sin(deg2),sin(deg2),cos(deg2) );

    //vec2 uv1 = np_uv * rotM1;
    //vec2 uv2 = np_uv * rotM2;
    //float f1 = moonsMask(uv1);
    //float f1Inv = moonsMask(uv2);

    
    //TODO : Aquí hacer un select de operación en base al tiempo
    //int final = int(f1) | int(f1Inv);
    //int final = int(f1) ^ int(f1Inv);
    int final = int(f1) & int(f1Inv);

    // Time varying pixel color
    vec3 col = vec3(final);

    // Output to screen
    fragColor = col;
}