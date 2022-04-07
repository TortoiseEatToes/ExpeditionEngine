#pragma pack_matrix( row_major )

Texture2D mainTexture: register(t0);

SamplerState aSampler : register(s0);

// Material properties
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

// Basic Phong Illumination computation
void PhongModel(
	Material mat,
	PhongADS lightint,
	float3 L,
	float3 normal,
	float3 DirToEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	// every light source adds to the ambient light total
	ambient = mat.Ambient * lightint.Ambient;

	float diffuseFactor = dot(L, normal);

	// Diffuse and specular contribution only if not facing away from light source
	if (diffuseFactor > 0.0f)
	{
		diffuse = diffuseFactor * mat.Diffuse * lightint.Diffuse;

		float3 r = reflect(-L, normal);		// Compute the reflected ray of light
		float spec_val = max(dot(r, DirToEye.xyz), 0);
		float specFactor = pow(spec_val, mat.Specular.w);
		spec = specFactor * mat.Specular * lightint.Specular;
	}
	else
	{
		diffuse = float4(0, 0, 0, 0);
		spec = float4(0, 0, 0, 0);
	}
}

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

//  Constant Buffers
cbuffer CamData : register(b0)
{
	float4x4 View;
	float4x4 Projection;
};

cbuffer LightParameters : register (b1)
{
	DirectionalLight DirLight[3];
	PointLight PntLightList[10];
	SpotLight SpLight[10];
	float4 EyePosWorld;
};

// Directional Light Computation
void ComputeDirectionalLight(
	Material mat,
	DirectionalLight DirLit,
	float4 normal,
	float4 DirToEye,
	float4x4 WorldInv,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	// Zeroing out the initial ADS contributions
	ambient = float4(0, 0, 0, 0);
	diffuse = float4(0, 0, 0, 0);
	spec = float4(0, 0, 0, 0);

	// we compute ligth in the model-space 
	// For directional light, the source is infinitely far, so translation have no effect
	float3 L = normalize(mul(-DirLit.Direction.xyz, (float3x3)WorldInv));

	PhongModel(mat, DirLit.LightInt, L, normal.xyz, DirToEye.xyz, ambient, diffuse, spec);
}

// Point Light Computation
void ComputePointLight(
	Material mat,
	PointLight PLight,
	float4 posms,
	float4 normal,
	float4 DirToEye,
	float4x4 WorldInv,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	// Zeroing out the ADS contributions
	ambient = float4(0, 0, 0, 0);
	diffuse = float4(0, 0, 0, 0);
	spec = float4(0, 0, 0, 0);

	// we compute the model-space position
	float3 litPosMS = mul(PLight.Position, WorldInv).xyz;
	float3 L = litPosMS - posms.xyz;

	// Early out if out of range
	float d = length(L);
	if (d > PLight.Attenuation.w)
		return;

	L /= d;	// normalize 

	PhongModel(mat, PLight.LightInt, L, normal.xyz, DirToEye.xyz, ambient, diffuse, spec);

	float test = d / PLight.Attenuation.w;

	// Now we attenuate based on range
	float att = 1 - dot(PLight.Attenuation.xyz, float3(test, test * 2, test * 3));

	ambient.xyz *= att;
	diffuse.xyz *= att;
	spec.xyz *= att;
}

// Spot Light Computation
void ComputeSpotLight(
	Material mat,
	SpotLight SptLight,
	float4 posms,
	float4 normal,
	float4 DirToEye,
	float4x4 WorldInv,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	// Zeroing out the ADS contributions
	ambient = float4(0, 0, 0, 0);
	diffuse = float4(0, 0, 0, 0);
	spec = float4(0, 0, 0, 0);

	// ****** Same calculations as Point Light  ****

	// we compute the model-space position
	float3 litPosMS = mul(SptLight.Position, WorldInv).xyz;
	float3 L = litPosMS - posms.xyz;

	float d = length(L);
	if (d > SptLight.Attenuation.w)
		return;

	L /= d;  // normalize 

	PhongModel(mat, SptLight.LightInt, L, normal.xyz, DirToEye.xyz, ambient, diffuse, spec);

	// Now we attenuate based on range
	float att = 1 / dot(SptLight.Attenuation.xyz, float3(1, d, d*d));

	// Ambient not attenuated
	diffuse *= att;
	spec *= att;

	// *****************************************

	// now we compute the spotlight factor
	float4 msLitDir = SptLight.Direction;
	msLitDir.w = 0; // making sure we have a vector and not a point
	msLitDir = normalize(mul(msLitDir, WorldInv));
	float spot = pow(max(dot(-L, msLitDir.xyz), 0), SptLight.Direction.w);

	ambient *= spot;
	diffuse *= spot;
	spec *= spot;
}



// ******* Shader operations

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 PosMS : POSITION;
	float4 Norm : NORMAL;
	float2 Tex : TEXCOORD;
	float4x4 world : INSTANCEWORLD;
	float4x4 WorldInv : INSTANCEWORLDINVERSE;
	float3x4 mat : INSTANCEMATERIAL;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(float4 Pos : POSITION, float4 nor : NORMAL, float2 tex : TEXCOORD, float4x4 world : INSTANCEWORLD, float4x4 worldInv : INSTANCEWORLDINVERSE, float3x4 mat : INSTANCEMATERIAL)
{
	VS_OUTPUT output;
	output.PosMS = Pos;  // We pass along the raw model space position 
	output.Norm = nor;	 // and the face normal
	output.world = world;
	output.WorldInv = worldInv;
	output.mat = mat;

	output.Pos = mul(Pos, world);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);

	output.Tex = tex;

	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
	int numDircs = 3;
	int numPoints = 10;
	int numSpots = 10;

	// Compute light values in model-space
	float4 msEyePos = mul(EyePosWorld, input.WorldInv);
	float4 msDirToEye = normalize(msEyePos - input.PosMS);

	float4 ambient = float4(0, 0, 0, 0);
	float4 diffuse = float4(0, 0, 0, 0);
	float4 spec = float4(0, 0, 0, 0);

	Material mat;
	mat.Ambient = input.mat[0];
	mat.Diffuse = input.mat[1];
	mat.Specular = input.mat[2];

	float4 A, D, S;

	for (int i = 0; i < numDircs; i++) {
		ComputeDirectionalLight(mat, DirLight[i], normalize(input.Norm), msDirToEye, input.WorldInv, A, D, S);

		ambient += A;
		diffuse += D;
		spec += S;
	}

	for (int i = 0; i < numPoints; i++) {
		ComputePointLight(mat, PntLightList[i], input.PosMS, normalize(input.Norm), msDirToEye, input.WorldInv, A, D, S);

		ambient += A;
		diffuse += D;
		spec += S;
	}


	for (i = 0; i < numSpots; i++) {
		ComputeSpotLight(mat, SpLight[i], input.PosMS, normalize(input.Norm), msDirToEye, input.WorldInv, A, D, S);

		ambient += A;
		diffuse += D;
		spec += S;
	}

	float4 litColor = ambient + diffuse + spec;

	//int test = input.id;

	float4 texColor = mainTexture.Sample(aSampler, input.Tex);

	litColor *= texColor;

	// Compute fog density as function of distance to eye
	//float distToEye = length(msEyePos - input.PosMS);
	//float FogPercent = saturate((distToEye - fog.FogStart) / fog.FogRange);  // See https://msdn.microsoft.com/en-us/library/windows/desktop/bb509645(v=vs.85).aspx
	//
	//// blend litcolor with fog level
	//// C_src = FogColor
	//// C_dst = litColor
	//// C = C_src * fogPercent + C_dst * (1 - fogPercent)
	//litColor = lerp(litColor, fog.FogColor, FogPercent);				// See https://msdn.microsoft.com/en-us/library/windows/desktop/bb509618(v=vs.85).aspx

	/****************************************************/



	return litColor;
}
