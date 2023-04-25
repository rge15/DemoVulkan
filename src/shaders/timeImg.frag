#version 450

#define PI 3.14156295358979

layout(set=0, binding=0, r16) uniform image2D storageImg;

layout(location = 0) in vec3 vertColor;
layout(location = 0) out vec3 fragColor;

layout(push_constant) uniform app_data_t
{
    float   width;
    float   height;
    float   iTime;
    float   rTime;
} data;

vec2 res = vec2(data.width,data.height);

float sdBox( in vec2 p, in vec2 b )
{
    vec2 d = abs(p)-b;
    return length(max(d,0.0)) + min(max(d.x,d.y),0.0);
}

float sdOrientedBox( in vec2 p, in vec2 a, in vec2 b, float th )
{
    float l = length(b-a);
    vec2  d = (b-a)/l;
    vec2  q = (p-(a+b)*0.5);
          q = mat2(d.x,-d.y,d.y,d.x)*q;
          q = abs(q)-vec2(l,th)*0.5;
    return length(max(q,0.0)) + min(max(q.x,q.y),0.0);    
}

float noiseValue;

vec2 t1boxPos = vec2( .8 ,  .5);
vec2 t1boxSiz = vec2( .3 , 0.1);

vec2 t2boxPos = vec2( .8 ,  .2);
vec2 t2boxSiz = vec2( .1 , 0.3);

float TIMEletter(in vec2 uv)
{
    float col = 0.;

    float box1  = smoothstep(0.01,0.,sdBox( uv+t1boxPos, t1boxSiz ));
    float box2  = smoothstep(0.01,0.,sdBox( uv+t2boxPos, t2boxSiz ));

    vec2 b3pos  = vec2(.3,.1);
    vec2 b3siz  = vec2(.075,0.2);
    float box3  = smoothstep(0.01,0.,sdBox( uv+b3pos, b3siz ));

    vec2 b8pos  = vec2(-.05,.1);
    vec2 b8siz  = vec2(.055,0.2);
    float box8  = smoothstep(0.01,0.,sdBox( uv+b8pos, b8siz ));

    vec2 b9pos  = vec2(-.35,.1);
    vec2 b9siz  = vec2(.055,0.2);
    float box9  = smoothstep(0.01,0.,sdBox( uv+b9pos, b9siz ));

    vec2 dpos   = vec2(-.28,.065);
    vec2 dp1   = vec2(-.05,-.05);
    vec2 dp2   = vec2(-.2,-.2);
    float thick = 0.1;
    float d1    = smoothstep(0.01,0.,sdOrientedBox(uv+dpos, dp1, dp2, thick));

    vec2 d2pos   = vec2(-.28,.065);
    vec2 d2p1   = vec2(-.11,-.05);
    vec2 d2p2   = vec2(.05,-.2);
    float d2    = smoothstep(0.01,0.,sdOrientedBox(uv+d2pos, d2p1, d2p2, thick));

    vec2 b4pos  = vec2(-.6,.12);
    vec2 b4siz  = vec2(.05,0.22);
    float box4  = smoothstep(0.01,0.,sdBox( uv+b4pos, b4siz ));

    vec2 b5pos  = vec2(-.7,.12);
    vec2 b5siz  = vec2(.1,0.04);
    float box5  = smoothstep(0.01,0.,sdBox( uv+b5pos, b5siz ));

    vec2 b6pos  = vec2(-.7,-.06);
    vec2 b6siz  = vec2(.13,0.04);
    float box6  = smoothstep(0.01,0.,sdBox( uv+b6pos, b6siz ));

    vec2 b7pos  = vec2(-.7,.3);
    float box7  = smoothstep(0.01,0.,sdBox( uv+b7pos, b6siz ));

    float t = box1 + box2;
    float i = box3;
    float m = box8 + box9 + d1 + d2;
    float e = box4 + box5 + box6 + box7;

    col += t + i + m + e;

    return clamp(0.,1.,col);
}

float TconvMask( in vec2 uv )
{
    float maxYVal1 = t1boxPos.y + t1boxSiz.y;

    float box1  = sdBox(uv + t1boxPos, t1boxSiz);
    float inbox1  = sdBox(uv + t1boxPos + vec2(0.,0.00),t1boxSiz - vec2(0.02,0.02));

    float maxYVal2 = t2boxPos.y + t2boxSiz.y;

    float box2  = sdBox(uv + t2boxPos, t2boxSiz);
    float inbox2  = sdBox(uv + t2boxPos + vec2(0.,0.01), t2boxSiz - vec2(0.01,0.01));

    float dbox1 = smoothstep(0.01,0.0,box1);
    dbox1 -= smoothstep(0.01,0.0,inbox1);
    dbox1 -= smoothstep(0.01,0.0,inbox2);

    float dbox2 = smoothstep(0.01,0.0,box2);
    dbox2 -= smoothstep(0.01,0.0,inbox2);
    dbox2 -= smoothstep(0.01,0.0,inbox1);

    float maxYValue = max(maxYVal1,maxYVal2);

    float applyMax = step(0.,(uv.y)+maxYValue);

    float final = (dbox1 + dbox2);

    return step( 0.8, final );
}

float N21(in vec2 p)
{
    p = 50.*fract( p * PI);
    p = 50.*fract((p+vec2(0.24342,709.23))/PI);

    return -1. + (2.*fract((p.x*p.y)) ) + 0.03;
}

float timeMark( in float timeDuration, in float timeStart )
{
    float t = step(0.,data.rTime-timeStart) * max( smoothstep(0.,timeDuration,mod(data.rTime-timeStart,timeDuration)), step(0.,data.rTime-timeStart-timeDuration));

    return  t;
}

float t = timeMark( .1 , 20. );

mat3 conv = mat3(vec3(0.85,0.75,0.65),
                 vec3(0.75, 0.0,0.55),
                 vec3(0.65,0.55,0.55)) * (1. + t * 0.5);

float pixelValueInFX( in vec2 p_pos )
{
    vec2 uv  = vec2((2.*p_pos.xy-res.xy) / res.y);

    float timeMark = TIMEletter(uv) * (1.-t);

    float tMask = TconvMask(uv) * (1.-t);
    float tMaskRandom = tMask * noiseValue;

    float imgReadMask = 1. - clamp( 0. , 1. , tMask + timeMark );
    vec4 r = imageLoad( storageImg, ivec2(p_pos.xy) ) * imgReadMask;
    
    float readFactor = 1.;
    if(data.rTime < 0.02)
        readFactor = 0.;
    r *= readFactor;

    return (tMaskRandom + r.x)/2.;

}

float kernelApply()
{
    float colsp = pixelValueInFX( gl_FragCoord.xy + vec2( -1., 1. ) ) * conv[0][0];
    float colep = pixelValueInFX( gl_FragCoord.xy + vec2(  0., 1. ) ) * conv[1][0];
    float colpp = pixelValueInFX( gl_FragCoord.xy + vec2(  1., 1. ) ) * conv[2][0];

    float colse = pixelValueInFX( gl_FragCoord.xy + vec2( -1., 0. ) ) * conv[0][1];
    float colpe = pixelValueInFX( gl_FragCoord.xy + vec2(  1., 0. ) ) * conv[2][1];

    float colss = pixelValueInFX( gl_FragCoord.xy + vec2( -1., -1.) ) * conv[0][2];
    float coles = pixelValueInFX( gl_FragCoord.xy + vec2(  0., -1.) ) * conv[1][2];
    float colps = pixelValueInFX( gl_FragCoord.xy + vec2(  1., -1.) ) * conv[2][2];
        
    float t = timeMark( 0.5, 3. ); 

    float col = (colsp + colep + colpp + colse + colpe + colss + coles + colps) / (3. - t);

    return col;
}

void main()
{
    vec2 uv = vec2((2.*gl_FragCoord.xy-res.xy)/res.y);

    noiseValue = N21( uv + data.rTime );

    float timeMark = TIMEletter(uv);

    //TODO : Meter todo esto en una función que te devuelva el valor en ese pixel

        
    float tMask = TconvMask(uv);
    
    /*
    float tMaskRandom = tMask * noiseValue;

    float imgReadMask = 1. - clamp( 0. , 1. , tMask + timeMark );
    vec4 r = imageLoad( storageImg, ivec2(gl_FragCoord.xy) ) * imgReadMask;
    float readFactor = 1.; 
    if(data.rTime < 0.02)
        readFactor = 0.;
    r *= readFactor;
    */
    

    float tKernelData = kernelApply();

    imageStore(storageImg, ivec2(gl_FragCoord.xy), vec4(tKernelData) );

    fragColor = vec3( tKernelData - timeMark );
}