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

    //Last Mom
    float lT = 1. - timeMark(3.,35.);
    float lT2 = 1. - timeMark(3.,37.);
    
    //First Modification
    float t1 = timeMark( 5.,0. ) * lT;
    float t2 = timeMark( 9.,5. ) * lT;
    float t3 = timeMark( 6.,9. ) * lT;

    float phase1 = t2 * 4.;
    float phase2 = t3 * 2.;
    //First Mod
    //Max Time 13.

    //Second Mod
    float t4 = timeMark( 4., 13.) * lT;
    
    float lineW1 = t4 * abs(sin( data.rTime * 0.2 + 0.3)) * 0.05;
    float lineW2 = t4 * abs(sin( data.rTime * 0.1 + 0.2)) * 0.05;
    float lineW3 = t4 * abs(sin( data.rTime * 0.3 + 0.1)) * 0.05;
    //Second Mod
    //Max Time 17.

    //Third Mod
    float t5 = timeMark( 9., 13.) * lT;

    float amp1 = -0.3 * t5;
    float amp2 = -0.1 * t5;
    float amp3 = -0.2 * t5;

    float phase3 = t5 * 5.5;
    float phase4 = t5 * 3.0;
    float phase5 = t5 * 2.0;
    //Third Mod

    //Fourth Mod
    float showOtherBands = timeMark(.5,20.) * lT;
    float t6 = timeMark( 8., 20. ) * lT;
    float t7 = timeMark( 5., 20. ) * lT;

    float phaseN1 = t6 * 4.;
    float phaseN2 = t7 * 1.;
    float colPhase1 = -t6;
    float colPhase2 = t7 * 1.5;
    float colPhase3 = -t7;
    //Fourth Mod

    //Fifth Mod
    float t8 = timeMark( 10.,25.) * lT;
    float t9 = timeMark( 5.,25.) * lT;
    float t0 = timeMark( 5.,30.) * lT;

    float speed1 = t8 * 1.5;
    float speed2 = t8 * 2.;
    float speed3 = t9 * 2. + t0 * -2.;
    float speed4 = t9 * 1. + t0 * -1.;
    float speed5 = t8 * .5;

    float ph1 = t8 * 2 * sin(data.rTime * 0.2);
    float ph2 = t9 * 4. - t0 * 4. * sin(data.rTime * 0.2);
    float ph3 = t9 * 6. - t0 * 3.;
    //Fifth Mod

    float rLineW = 0.1 + lineW1;
    float gLineW = 0.1 + lineW2;
    float bLineW = 0.1 + lineW3;

    float commonAmp = 1. * t1;

    float rAmp = commonAmp + amp1;
    float gAmp = commonAmp + amp2;
    float bAmp = commonAmp + amp3;

    float rPh = phase1 + phase5 + t8 + colPhase1+ ph3 * 0.5;
    float gPh = phase2 + phase3 + ph3 + colPhase2;
    float bPh = phase4 + ph1 + colPhase3 + sin(data.iTime * 0.3) * t2;

    float rAngSp = 1. + speed3;
    float gAngSp = 1. + speed4;
    float bAngSp = 1. + speed5;
    float n1AngSp = 1. + speed1;
    float n2AngSp = 1. + speed2;

    float rForm = rAmp * sin(uv.y * rAngSp + data.rTime+rPh);
    float gForm = gAmp * sin(uv.y * gAngSp + data.rTime+gPh);
    float bForm = bAmp * sin(uv.y * bAngSp + data.rTime+bPh);
    float nForm1 = bAmp * sin(uv.y * n1AngSp + data.rTime+bPh+phaseN1 + ph2);
    float nForm2 = bAmp * sin(uv.y * n2AngSp + data.rTime+bPh+phaseN2 + ph3);

    float rLine1 = smoothstep(0.1,0., uv.x - rLineW + rForm );
    float rLine2 = smoothstep(0.,0.1, uv.x + rLineW + rForm );

    float gLine1 = smoothstep(0.1,0., uv.x - gLineW + gForm );
    float gLine2 = smoothstep(0.,0.1, uv.x + gLineW + gForm );
    
    float bLine1 = smoothstep(0.1,0., uv.x - bLineW + bForm );
    float bLine2 = smoothstep(0.,0.1, uv.x + bLineW + bForm );

    float n1Line1 = smoothstep(0.1,0., uv.x - bLineW + nForm1 );
    float n1Line2 = smoothstep(0.,0.1, uv.x + bLineW + nForm1 );

    float n2Line1 = smoothstep(0.1,0., uv.x - bLineW + nForm2 );
    float n2Line2 = smoothstep(0.,0.1, uv.x + bLineW + nForm2 );

    float r = float(int(rLine2) & int(rLine1));
    float g = float(int(gLine2) & int(gLine1));
    float b = float(int(bLine2) & int(bLine1));
    float n1 = float(int(n1Line2) & int(n1Line1)) * showOtherBands;
    float n2 = float(int(n2Line2) & int(n2Line1)) * showOtherBands;

    vec3 n1Col = n1 * vec3( 1. , 0.5 , 0. );
    vec3 n2Col = n2 * vec3( .48 , 0.15 , .51 );

    // Time varying pixel color
    vec3 col =  vec3(r,g,b) + n1Col + n2Col;

    col = vec3(clamp(0.,1.,col.r),clamp(0.,1.,col.g),clamp(0.,1.,col.b));

    // Output to screen
    fragColor = col * lT2;
}