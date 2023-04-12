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

struct Blob
{
    vec2 center;
    vec2 axis_speed;
    vec3 color;
    float radius;
    
};

const int numBlobs = 5;
const float distBlobs = 1./float(numBlobs);

float N21_limitless( in vec2 p )
{
    p = 50.*fract( p/PI + vec2(0.71,0.113) );

    return -1. + 2. * fract( p.x*p.y*(p.x+p.y)); 
}

float N21_normal(vec2 co)
{
    return fract(N21_limitless(co));
}


Blob blobs[numBlobs];
vec2 N12(in int i)
{
    vec2 value = vec2(i, i+1); 
    return normalize(value);
}

void main()
{
    vec2 res = vec2(data.width,data.height);
    vec2 uv = (2.*gl_FragCoord.xy-res.xy)/res.y;
    
    uv *= 1.5;

    for(int i = 0 ; i < numBlobs; i++)
    {
        blobs[i].center = vec2(float(i+1)*distBlobs);
        
        float speedX = N21_limitless(vec2(i));
        float speedY = N21_limitless(vec2(i+2));
        speedX = mod(speedX,4.);
        speedY = mod(speedY,4.);
        blobs[i].axis_speed = vec2(speedX, speedY);
        
        blobs[i].center.x *= sin(speedX*data.rTime);
        blobs[i].center.y *= cos(speedY*data.rTime);
    
        blobs[i].radius = N21_normal(vec2(i));
     
        float colX = N21_normal(vec2(i+5,i));
        float colY = N21_normal(vec2(i,i+3));
        float colZ = N21_normal(vec2(i+2,i+7));
        blobs[i].color = vec3(colX,colY,colZ);
    }

    float length_blob = 1.;
    float length_total = 1.;
    vec3 color = vec3(1.);
    
    for(int i = 0 ; i < numBlobs; i++)
    {
        length_blob = length(uv-blobs[i].center);
        length_total *= length_blob;
        length_blob = 1.-length_blob;
        color += length_blob*blobs[i].color;
    }

    length_total = smoothstep(0.,1.,clamp(1.-length_total,0.,1.));
    length_total = 1.-length_total;

    // Time varying pixel color
    vec3 col = vec3(length_total*color);

    // Output to screen
    fragColor = vec3(col);
}