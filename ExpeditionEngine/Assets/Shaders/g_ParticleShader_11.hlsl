#pragma pack_matrix( row_major )
Texture2D mainTexture : register(t0);

SamplerState aSampler : register(s0);

cbuffer CamData : register(b0)
{
	float4x4 View;
	float4x4 Projection;
}

struct VS_INPUT
{
	float4 Pos : POSITION;
	float4x4 World : INSTANCE_WORLD;
	float4 Tint: INSTANCE_TINT;
	float2 Tex : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 PosMS : POSITION;
	float2 Tex : TEXCOORD;
	float4x4 World : INSTANCE_WORLD;
	float4 Tint: INSTANCE_TINT;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;

	output.PosMS = input.Pos;  // We pass along the raw model space position
	
	output.Pos = mul(input.Pos, input.World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	
	output.Tex = input.Tex;
	output.Tint = input.Tint;

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


	litColor.x = (litColor.x + input.Tint.x) * 0.5f;
	litColor.y = (litColor.y + input.Tint.y) * 0.5f;
	litColor.z = (litColor.z + input.Tint.z) * 0.5f;
	//litColor.a = (litColor.a + input.Tint.a) * 0.5f; //TODO, figure out if we can do this properly

	//float4 msEyePos = mul(EyePosWorld, input.WorldInv);

	//float distToEye = length(msEyePos - input.PosMS);
	//float FogPercent = saturate((distToEye - fog.FogStart) / fog.FogRange);  // See https://msdn.microsoft.com/en-us/library/windows/desktop/bb509645(v=vs.85).aspx
	//
	//litColor = lerp(litColor, fog.FogColor, FogPercent);
	//
	return litColor;
}