#pragma pack_matrix( row_major )

struct Material
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;  // Hack: w holds the specular power
};

// Light properties
struct PhongADS
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
};

// Directional Light Data
struct DirectionalLight
{
	PhongADS LightInt;
	float4 Direction;
};

// Point Light data
struct PointLight
{
	PhongADS LightInt;
	float4 Position;
	float4 Attenuation; //Hack: Range in w
};

// Spot light data
struct SpotLight
{
	PhongADS LightInt;
	float4 Position;
	float4 Attenuation; //Hack: Range in w
	float4 Direction; //Hack: Spot Exp in w
};

cbuffer Data_PerFrame : register(b0)
{
	DirectionalLight DirLight[3];
	PointLight PntLightList[10];
	SpotLight SptLightList[10];
	float4x4 View;
	float4x4 Projection;
	float4 EyePosWorld;
};


void VS(float4 pos : POSITION, out float4 outPos : SV_POSITION, out float4 outColor : COLOR, float4x4 world : INSTANCE_WORLD,  float4 color : INSTANCE_COLOR)
{
	outPos = mul(pos, world);
	outPos = mul(outPos, View);
	outPos = mul(outPos, Projection);
	outColor = color;
}

float4 PS(float4 pos : SV_POSITION, float4 color : COLOR) : SV_Target
{
	return color;
}