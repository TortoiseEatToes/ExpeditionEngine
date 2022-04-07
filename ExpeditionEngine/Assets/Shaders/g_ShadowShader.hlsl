#pragma pack_matrix( row_major )

cbuffer Data_Shadow: register(b0)
{
	float4x4 View;
	float4x4 Projection;
};

struct VS_INPUT
{
	float4x4 World : INSTANCE_WORLD;
	float4 Pos : POSITION;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT vin)
{
	VS_OUTPUT output;

	output.Pos = mul(vin.Pos, vin.World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);


	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 output;
	output.xyz = input.Pos.z;
	output.w = 1.0f;

	return output;
}