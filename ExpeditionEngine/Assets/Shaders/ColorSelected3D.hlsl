#pragma pack_matrix( row_major )

cbuffer CamData : register(b0)
{
	float4x4 View;
	float4x4 Projection;
}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION, uint InstanceID : SV_InstanceID, float4x4 world : INSTANCEWORLD, float4 color : INSTANCECOLOR )
{
	VS_OUTPUT output;

	output.Pos = mul(Pos, world);
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    output.Color = color;
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
    return input.Color;
}
