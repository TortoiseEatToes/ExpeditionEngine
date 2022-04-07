#pragma pack_matrix( row_major )

struct Fog {
	float FogStart;
	float FogRange;
	float4 FogColor;
};

Texture2D mainTexture : register(t0);

SamplerState aSampler : register(s0);

cbuffer CamData : register(b0)
{
	float4x4 View;			
	float4x4 Projection;
}

cbuffer FogData : register(b2) {
	Fog fog;
	float4 EyePosWorld;
}
//--------------------------------------------------------------------------------------

struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;	
	float4x4 world : INSTANCEWORLD;
	float4x4 WorldInv : INSTANCEWORLDINVERSE;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 PosMS : POSITION;
	float2 Tex : TEXCOORD;
	float4x4 world : INSTANCEWORLD;
	float4x4 WorldInv : INSTANCEWORLDINVERSE;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( VS_INPUT input)
{
	VS_OUTPUT output;

	output.PosMS = input.Pos;  // We pass along the raw model space position
	output.world = input.world;
	output.WorldInv = input.WorldInv;

	output.Pos = mul(input.Pos, input.world);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);

	output.Tex = input.Tex;
	
	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{


	float4 litColor = mainTexture.Sample(aSampler, input.Tex);

	if (litColor.a < 0.2f)
		discard;

	//float4 msEyePos = mul(EyePosWorld, input.WorldInv);

	//float distToEye = length(msEyePos - input.PosMS);
	//float FogPercent = saturate((distToEye - fog.FogStart) / fog.FogRange);  // See https://msdn.microsoft.com/en-us/library/windows/desktop/bb509645(v=vs.85).aspx
	//
	//litColor = lerp(litColor, fog.FogColor, FogPercent);
	//
	return litColor;
}