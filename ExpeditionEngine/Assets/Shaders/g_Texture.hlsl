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

SamplerState aSampler : register(s0);

cbuffer Data_PerFrame : register(b0)
{
	DirectionalLight DirLight[3];
	PointLight PntLightList[10];
	SpotLight SptLightList[10];
	float4x4 View;
	float4x4 Projection;
	float4 EyePosWorld;
};

Texture2D mainTexture[] : register(t0);

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4x4 world : INSTANCE_WORLD;
	float4x4 worldInv : INSTANCE_WORLDINVERSE;
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
	uint textureName : INSTANCE_TEXTURE;
};

struct VS_OUTPUT
{
	float4x4 world : INSTANCE_WORLD;
	float4x4 worldInv : INSTANCE_WORLDINVERSE;
	float4 Pos : SV_POSITION;
	float4 PosMS : POSITION;
	float2 Tex : TEXCOORD;
	uint textureName : INSTANCE_TEXTURE;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( VS_INPUT input)
{
	VS_OUTPUT output;

	output.PosMS = input.Pos;  // We pass along the raw model space position
	output.world = input.world;
	output.worldInv = input.worldInv;

	output.Pos = mul(input.Pos, input.world);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);

	output.Tex = input.Tex;
	output.textureName = input.textureName;
	
	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 litColor = mainTexture[input.textureName].Sample(aSampler, input.Tex);

	//if (litColor.a < 0.2f)
	//	discard;

	return litColor;
}