#version 450

#define NUM_STEPS_MARCH 60
#define COLISION_DIST 0.00001
#define MAX_RAY_LENGTH 10000.0 

layout(location = 0) in vec3 vertColor;
layout(location = 0) out vec3 fragColor;

layout(push_constant) uniform app_data_t
{
    float   width;
    float   height;
    float   time;
} data;

float GetDist( in vec3 p_rO )
{
    float spDist = length(p_rO - vec3(0.,1.,2.)) - 1.; 
    float plDist = p_rO.y;
    
    return min(plDist, spDist);
}

float RayMarch(in vec3 rO, in vec3 rD )
{
    float d = 0.;
    for(int i = 0; i < NUM_STEPS_MARCH; i++)
    {
        vec3 centerP = rO + rD*d;
        float dist = GetDist(centerP);
        d += dist;

        if(d > MAX_RAY_LENGTH || dist < COLISION_DIST)
            return d; 
    }

    return d;
}

vec3 GetNormal(in vec3 p_pos)
{
    float dist = GetDist(p_pos);

    vec2 sub = vec2(0.1,0.);

    vec3 normal = 
        normalize(dist - vec3(
            GetDist( p_pos - sub.xyy ),
            GetDist( p_pos - sub.yxy ),
            GetDist( p_pos - sub.yyx )
        ));
    
    return normal;
}

float GetLight(in vec3 pPos)
{
    vec3 lightPos = vec3(sin(data.time),cos(data.time) + 2.,-1.);
    vec3 ligthDir = normalize(lightPos - pPos);

    vec3 pointNormal = GetNormal(pPos);

    float l = clamp(dot( pointNormal, ligthDir),0.,1.);

    float ligthMarch    = RayMarch( pPos + pointNormal * 2. * COLISION_DIST, ligthDir );
    float ligthDist     = length( lightPos - pPos );

    if( ligthDist > ligthMarch )
        l *= 0.1;

    return l; 
}

void main()
{
    vec2 res = vec2(data.width,data.height);
    vec2 uv = vec2((2.*gl_FragCoord.xy-res.xy)/res.y);

    uv.y *= -1; 

    vec3 camO   = vec3(0.,1.,0.);
    vec3 camDir = vec3(uv, 1.);

    float d = RayMarch(camO, camDir);

    vec3 pointPos = camO + camDir * d;
    float lightPow = GetLight(pointPos);

    fragColor = vec3(lightPow);
}