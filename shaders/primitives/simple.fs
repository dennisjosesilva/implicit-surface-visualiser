#version 410

// Fragment shader

layout(location = 0) in vec3 posFS;
layout(location = 1) in vec3 normalFS;

out vec4 fColor;

void main()
{
  vec3 lightPos = vec3(3.0, 0.0, 2.0) * 10.0;
  vec3 lightColor = vec3(1.0);

  vec3 matColor = vec3(0.53, 0.80, 0.87);
  vec3 matSpecColor = vec3(1.0);

  float matAmbientCoeff = 0.2;
  float matDiffuseCoeff = 0.3;
  float matSpecularCoeff = 0.8;

  vec3 normal;
  normal = normalize(normalFS);

  vec3 surfToLight = normalize(lightPos - normalFS);
  float diffuseCoeff = max(0.0, dot(surfToLight, normal));

  vec3 cameraPosition = vec3(0.0);
  vec3 surfToCamera = normalize(cameraPosition - posFS);
  vec3 reflected = 2.0f * diffuseCoeff * normal - surfToLight; 
  float specularCoeff = max(0.0, dot(reflected, surfToCamera));

  vec3 compColor = min(1.0, 
    matAmbientCoeff + matDiffuseCoeff * diffuseCoeff) * lightColor * matColor;
  compColor += matSpecularCoeff * specularCoeff * lightColor * matSpecColor;

  fColor = vec4(compColor, 1.0);
  // fColor = vec4(1.0, 0.0, 0.0, 1.0);
}