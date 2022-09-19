#version 410
// Vertex shader

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

layout (location = 0) out vec3 posFS;
layout (location = 1) out vec3 normalFS;

void main()
{
  gl_Position = projectionMatrix * modelViewMatrix * vec4(pos, 1.0);

  posFS = vec3(modelViewMatrix * vec4(pos, 1.0));
  normalFS = normalize(normalMatrix * normal);
}