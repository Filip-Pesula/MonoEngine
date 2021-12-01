#version 430

layout(location = 0) out vec4 color;
in vec4 pos;
in vec3 Normal;
in vec3 FragPos;
in vec2 texturePos;
in float vecZ;
in mat3 tangentBase;
vec3 lightPos = vec3(-10,10,-10);
layout(binding=0) uniform sampler2D textureSampler;
layout(binding=1) uniform sampler2D normalSampler;
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
	float u = texturePos.x;
	float v = texturePos.y;
	vec2 rTexturePos = (vec2((u),(v))/vecZ);


	vec3 textureNormal;
	textureNormal = texture(normalSampler, rTexturePos).rgb * 2 - 1;
	//textureNormal = vec3(-1,-1,1) * textureNormal;
	vec3 mNormal = textureNormal * inverse(tangentBase);
	//vec3 mNormal = TNB * (textureNormal*2 - 1);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(mNormal, lightDir), 0.0);
	float ambient = 0.3;
	float power = 1;
	diff = (diff * power * (1-ambient) + ambient);
	//vec4 sub_color = vec4((pos.xyz * diff),1.0);
	vec3 textureColore;
	textureColore = texture(textureSampler, rTexturePos).xyz;
	color = vec4((textureColore * diff),1.0);
}