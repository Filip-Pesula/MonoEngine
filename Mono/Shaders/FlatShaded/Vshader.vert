#version 430
#define M_PI 3.1415926535897932384626433832795
layout(location = 0) in vec4 point_array;
layout(location = 1) in vec4 normal_array;
layout(location = 2) in vec4 color_array;
uniform vec4 uPosition;
uniform vec3 uRotation;
uniform vec3 uScale;
uniform vec3 uScreenScale;
uniform vec3 uCamPosition;
uniform vec3 uCamRotation;
vec3 CamPosition = vec3(0,0,-10);
vec3 CamRotation = vec3(0,-10,0);
float FOWindex;

vec3 WordPosition;
vec3 ProjectionPosition;
vec3 ClippingPosition;

vec3 Rescaled;
vec4 resized;
out vec4 pos;
out vec3 Normal;
out vec3 FragPos;

vec3 Anticliping(vec3 iPosition)
{
	float zP = iPosition.z;
	if(zP < 0)
	{
		return iPosition;
	}
	float zC = 1 - 1/ pow(2, zP/10);
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
	WordPosition = point_array.xyz * uScale;
	mat3 rtm = getRotMatrinx(uRotation);
	WordPosition = rtm * WordPosition;
	WordPosition = WordPosition + uPosition.xyz;

    vec3 CameraToVec = uPosition.xyz - uCamPosition;
	vec3 Offset  = WordPosition + CameraToVec;
	mat3 rtm1 = getRotMatrinx(uCamRotation);
	Offset = rtm1 * Offset;
	ProjectionPosition = Offset - CameraToVec;
	//vec4 cameraProjected = vec4(Offset - CameraToVec , 10.0);
	float projectionScale = (ProjectionPosition.z + 10) * 0.05;
	ProjectionPosition.x = ProjectionPosition.x / projectionScale;
	ProjectionPosition.y = ProjectionPosition.y / projectionScale;

	ClippingPosition = Anticliping(ProjectionPosition);

	resized = vec4(uScreenScale * ClippingPosition, 10.0);

	gl_Position = resized;
	pos = color_array;
	FragPos = (resized + uPosition).xyz;
	Normal = rtm * normal_array.xyz;
}