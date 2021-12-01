#version 430

layout(location = 0) out vec4 color;
in vec4 pos;
in vec3 Normal;
in vec3 FragPos;
vec3 lightPos = vec3(-10,10,-10);
void main()
{
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(Normal, lightDir), 0.0);
	diff = diff +0.3;
	color = vec4((pos.xyz * diff),1.0);
}