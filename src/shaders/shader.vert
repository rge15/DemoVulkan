#version 450

layout(location = 0) out vec3 vertColor;

vec3 position[6] = vec3[](
    vec3( -1., -1., 0.),
    vec3( 1., 1., 0.),
    vec3(-1., 1., 0.),
    vec3( -1., -1., 0.),
    vec3( 1., -1., 0.),
    vec3( 1., 1., 0.)
);

vec3 color[3] = 
{
    vec3(1.0,0.,0.),
    vec3(0.,1.,0.),
    vec3(0.,0.,1.)
};

void main()
{
    gl_Position = vec4(position[gl_VertexIndex],1.);
    vertColor = color[gl_VertexIndex%3];
}
