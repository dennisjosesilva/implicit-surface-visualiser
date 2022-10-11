#version 410 core
// Vertex shader

layout (location = 0) in vec3 pos;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

void main() 
{
  gl_Position = projectionMatrix * modelViewMatrix * vec4(pos, 1.0);  
}

