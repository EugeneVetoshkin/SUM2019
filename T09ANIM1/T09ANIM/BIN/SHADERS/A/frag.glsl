/* VG4 */
#version 420

layout(location = 0) out vec4 Color;
uniform float Time;
//int n = gl_VertexID;

void main( void )
{
  Color = vec4(1 * sin(Time) , 1, 1, 1);
}

