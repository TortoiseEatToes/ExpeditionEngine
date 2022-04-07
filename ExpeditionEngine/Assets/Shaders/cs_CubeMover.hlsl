#pragma pack_matrix( row_major )

struct cbPerObject
{
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
	float4x4 pad1;
};

StructuredBuffer<cbPerObject> Buffer0 : register(t0);
RWStructuredBuffer<cbPerObject> BufferOut : register(u0);

[numthreads(1, 1, 1)]
void main( uint3 DTid : SV_DispatchThreadID )
{
	BufferOut[0].World = Buffer0[0].World;
	BufferOut[0].World._41 += 0.1;
}