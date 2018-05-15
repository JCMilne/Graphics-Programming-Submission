#version 400

in vec3 TexCoord;

layout (location = 0) out vec4 FragColor;
uniform vec4 innerColor;
uniform vec4 outerColor;
uniform float innerRadius;
uniform float outerRadius;

void main() 
{
 float dx = TexCoord.x - 0.75;
 float dy = TexCoord.y - 0.75;
 float dist = sqrt(dx * dx + dy * dy);
 FragColor = mix( innerColor,outerColor, smoothstep (innerRadius, outerRadius, dist ) );
}