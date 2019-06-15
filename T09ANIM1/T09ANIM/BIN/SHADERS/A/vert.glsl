/* VG4 */
#version 420

layout(location = 0) in vec3 InPosition;
uniform float Time;
uniform mat4 MatrWVP;

void main( void )
{
  int n = gl_VertexID;
                     
  gl_Position = sin(Time + n) + MatrWVP * vec4(InPosition, 1);
}
