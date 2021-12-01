#version 430

layout(location = 0) out vec4 color;
in vec4 pos;
in vec3 Normal;
in vec3 FragPos;
in vec2 texturePos;
in float vecZ;
vec3 lightPos = vec3(-10,10,-10);
layout(binding=0) uniform sampler2D textureSampler;
float Anticliping(float iPosition)
{
	float zP = iPosition;
	if(zP <= 0)
	{
		return iPosition;
	}
	float zC = -(10 * log(-(zP-10)/10))/log(2);
	//float zC = 10 - 10/ pow(2, zP/10);
	iPosition = zC;
	return iPosition;
}

void main()
{
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(Normal, lightDir), 0.0);
	diff = diff +0.3;
	//vec4 sub_color = vec4((pos.xyz * diff),1.0);
	float u = texturePos.x;
	float v = texturePos.y;
	float z = Anticliping(gl_FragDepth); 
	vec2 rTexturePos = (vec2((u),(v))/vecZ);
	vec3 textureColore;
	textureColore = texture(textureSampler, rTexturePos).xyz;
	color = vec4((textureColore * diff),1.0);
}