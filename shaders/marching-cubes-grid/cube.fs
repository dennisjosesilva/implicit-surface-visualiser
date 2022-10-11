#version 410 core 

// Fragment shader 

out vec4 fColor;

void main()
{
  // draw cube edges as light grey.
  fColor = vec4(0.8196, 0.0471, 0.0471, 1.0);
}