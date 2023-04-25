#version 450

layout(location = 0) in vec3 vertColor;
layout(location = 0) out vec3 fragColor;

layout(push_constant) uniform app_data_t
{
    float   width;
    float   height;
    float   iTime;
    float   rTime;
} data;

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

void main()
{
    vec2 res = vec2(data.width,data.height);
    vec2 uv = vec2((2.*gl_FragCoord.xy-res.xy)/res.y);

    vec3 col = vec3(0.);

    vec2 b1pos  = vec2( .85 , .4 );
    vec2 b1siz  = vec2( .3 , .3 );
    vec2 b12siz = vec2( .1 , .1 );

    float innerbox1 = smoothstep(0.01,0.,sdBox( uv+b1pos, b12siz ));
    float box1      = smoothstep(0.01,0.,sdBox( uv+b1pos, b1siz  )) - innerbox1;

    vec2 b2pos  = vec2( .75, -.1 );
    vec2 b2siz  = vec2( .4,  .4 );
    vec2 b22siz = vec2( .2,  .2 );

    float innerbox2 = smoothstep(0.01,0.,sdBox( uv+b2pos, b22siz ));
    float box2      = smoothstep(0.01,0.,sdBox( uv+b2pos, b2siz )) - innerbox2;

    vec2 b3pos  = vec2( .0, .5 );
    vec2 b3siz  = vec2(.075,0.2);
    float box3  = smoothstep(0.01,0.,sdBox( uv+b3pos, b3siz ));

    vec2 b4pos  = vec2( -.4   ,  .5 );
    vec2 b4siz  = vec2(  .075 ,  .2  );
    float box4  = smoothstep(0.01,0.,sdBox( uv+b4pos, b4siz ));

    vec2 b5pos  = vec2( -.4  ,  .6  );
    vec2 b5siz  = vec2(  .15 ,  .05 );
    float box5  = smoothstep(0.01,0.,sdBox( uv+b5pos, b5siz ));

    vec2 b6pos  = vec2(  -.04  ,  -.2  );
    vec2 b6siz  = vec2(  .08 ,   .08 );
    float box6  = smoothstep( 0.01 , 0. , sdBox( uv+b6pos, b6siz ) );

    vec2 dpos  = vec2(  .0  , -.4  );
    vec2 dp1   = vec2( -.11 , -.05 );
    vec2 dp2   = vec2(  .2  , -.35  );
    float thick = length( dp1-dp2 ); 
    float d1    = smoothstep(0.01,0.,sdOrientedBox(uv+dpos, dp1, dp2, thick));

    vec2 b7pos  = vec2( -.75 , -.2 );
    vec2 b7siz  = vec2( 0.25 );
    float box7  = smoothstep(0.01,0.,sdBox( uv+b7pos, b7siz ));

    vec2 b8pos  = vec2( -.75 , -.1 );
    vec2 b8siz  = vec2( 0.10 , .19 );
    float box8  = smoothstep(0.01,0.,sdBox( uv+b8pos, b8siz ));

    vec2 b9pos  = vec2( -.75 , -.6 );
    vec2 b9siz  = vec2( 0.25 , 0.2 );
    float box9  = smoothstep(0.01,0.,sdBox( uv+b9pos, b9siz ));

    vec2 b10pos  = vec2( -.65 , -.55 );
    vec2 b10siz  = vec2( 0.2 ,  0.12 );
    float box10  = smoothstep(0.01,0.,sdBox( uv+b10pos, b10siz ));

    float b = box1 + box2;
    float i = box3;
    float t = box4 + box5;
    float o = d1 - box6;
    float y = box7 - box8 + box9 - box10;

    col += 1. - (b + i + t + o + y);

    fragColor = col;
}