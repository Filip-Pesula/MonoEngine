#version 430
#define M_PI 3.1415926535897932384626433832795
layout(location = 0) in vec4 point_array;
layout(location = 1) in vec3 normal_array;
layout(location = 2) in vec3 tangent_array;
layout(location = 3) in vec3 bitangent_array;
layout(location = 4) in vec2 texture_array;
//layout(location = 3) in vec4 color_array;

uniform vec4 uPosition;
uniform mat4 uRotation;
uniform vec3 uScale;

uniform mat4 uModelMatrix;

uniform vec3 uScreenScale;
uniform vec3 uCamPosition;
uniform vec3 uCamRotation;

uniform mat4 uViewMatrix;

uniform mat4 uProjectionMatrix;


float FOWindex;

vec4 WordPosition;
vec4 ProjectionPosition;
vec3 ClippingPosition;

vec3 Rescaled;
vec4 resized;

out vec4 pos;
out vec3 Normal;
out vec3 FragPos;
out vec3 ReadFragPos;
out vec2 texturePos;
out float vecZ;
out mat3 tangentBase;

vec3 Anticliping(vec3 iPosition)
{
	float zP = iPosition.z;
	if(zP <= 0)
	{
		return iPosition;
	}
	float zC = 10 - 10/ pow(2, zP/10);
	iPosition.z = zC;
	return iPosition;
}

mat3 getRotMatrinx(vec3 mRotation)
{
	mRotation = radians(mRotation);
	float sinX = sin(mRotation.z);
	float cosX = cos(mRotation.z);
	float sinY = sin(mRotation.y);
	float cosY = cos(mRotation.y);
	float sinZ = sin(mRotation.x);
	float cosZ = cos(mRotation.x);
	mat3 RotatinMatrix;
	RotatinMatrix[0] = vec3(cosX*cosY, 	cosX*sinY*sinZ - sinX*cosZ,		cosX*sinY*cosZ + sinX*sinZ);
	RotatinMatrix[1] = vec3(sinX*cosY, 	sinX*sinY*sinZ + cosX*cosZ,		sinX*sinY*cosZ - cosX*sinZ);
	RotatinMatrix[2] = vec3( -sinY	 , 			cosY*sinZ		  ,				cosY*cosZ);
	return RotatinMatrix;
};

void main()
{
	//mat3 rtm = getRotMatrinx(uRotation);

	WordPosition = point_array * uModelMatrix;
	WordPosition.w = 1;

	ProjectionPosition = (WordPosition);

	
    vec3 CameraToVec = uPosition.xyz - uCamPosition;
	vec3 Offset  = WordPosition.xyz + CameraToVec;
	mat3 rtm1 = getRotMatrinx(uCamRotation);
	Offset = rtm1 * Offset;
	ProjectionPosition = vec4(Offset.xy, Offset.z - 10, 1);// - CameraToVec;
	
	
	if(ProjectionPosition.z > -10)
	{
		float projectionScale = (ProjectionPosition.z + 10) * 0.05;
		ProjectionPosition.x = ProjectionPosition.x / projectionScale;
		ProjectionPosition.y = ProjectionPosition.y / projectionScale;
	}
	else
	{
		ProjectionPosition.z = -100;
	}


	ClippingPosition = Anticliping(ProjectionPosition.xyz);

	resized = vec4(uScreenScale * ClippingPosition, 10.0);
	vecZ = 1/((ProjectionPosition.z+10));
	gl_Position = resized;

	FragPos = WordPosition.xyz;
	Normal = (inverse(uRotation) * vec4(normal_array.xyz,1)).xyz;
	texturePos = ((texture_array) / (ProjectionPosition.z+10));
	vec3 normal = normalize((inverse(uRotation) * vec4(normal_array.xyz,1)).xyz);
	vec3 tangent = normalize((inverse(uRotation) * vec4(tangent_array.xyz,1)).xyz);
	vec3 bitangent = normalize((inverse(uRotation) * vec4(bitangent_array.xyz,1)).xyz);
	tangentBase = mat3(tangent, bitangent, normal);
}