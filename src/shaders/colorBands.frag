#version 450

layout(location = 0) out vec3 fragColor;

layout(push_constant) uniform app_data_t
{
    float   width;
    float   height;
    float   iTime;
    float   rTime;
} data;


float timeMark( in float timeDuration, in float timeStart )
{
    float t = step(0.,data.rTime-timeStart) * max( smoothstep(0.,timeDuration,mod(data.rTime-timeStart,timeDuration)), step(0.,data.rTime-timeStart-timeDuration));

    return  t;
}

float normalTimeMark( in float timeDuration, in float timeStart  )
{
    float time = step(0.,data.rTime-timeStart) * max( smoothstep(0.,1.,mod(data.rTime-timeStart,timeDuration)), step(0.,data.rTime-timeStart-timeDuration));

    return time;
}

void main()
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 res = vec2(data.width, data.height);
    vec2 uv = (2.*gl_FragCoord.xy-res.xy)/res.y;

    float t1 = timeMark( 3.,0. );
    //float t2 = normalTimeMark( 3.,3. );

    float phase1 = timeMark( 3. , 3. );

    float rLineW = 0.1;
    float gLineW = 0.1;
    float bLineW = 0.1;

    float commonAmp = 1. * t1;

    float rAmp = commonAmp;
    float gAmp = commonAmp;
    float bAmp = commonAmp;

    float rPh = 2. * phase1;
    float gPh = 0.;
    float bPh = 0.;

    float rForm = rAmp * sin(uv.y+data.rTime+rPh) ;
    float gForm = gAmp * sin(uv.y+data.rTime+gPh) ;
    float bForm = bAmp * sin(uv.y+data.rTime+bPh) ;

    float rLine1 = smoothstep(0.1,0., uv.x - rLineW + rForm );
    float rLine2 = smoothstep(0.,0.1, uv.x + rLineW + rForm );

    float gLine1 = smoothstep(0.1,0., uv.x - gLineW + gForm );
    float gLine2 = smoothstep(0.,0.1, uv.x + gLineW + gForm );
    
    float bLine1 = smoothstep(0.1,0., uv.x - bLineW + bForm );
    float bLine2 = smoothstep(0.,0.1, uv.x + bLineW + bForm );

    float r = float(int(rLine2) & int(rLine1));
    float g = float(int(gLine2) & int(gLine1));
    float b = float(int(bLine2) & int(bLine1));


    // Time varying pixel color
    vec3 col = vec3(r,g,b);

    // Output to screen
    fragColor = col;
}