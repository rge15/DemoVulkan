#version 450

layout(location = 0) in vec3 vertColor;
layout(location = 0) out vec3 fragColor;

layout(push_constant) uniform app_data_t
{
    float   width;
    float   height;
    float   time;
} data;

void main()
{
    vec2 res = vec2(data.width,data.height);
    vec2 uv = vec2((2.*gl_FragCoord.xy-res.xy)/res.y);

    fragColor = vec3(uv, data.time);
}