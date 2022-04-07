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


struct perFrame
{
	DirectionalLight DirLight[3];
	PointLight PntLightList[10];
	SpotLight SptLightList[10];
	float4x4 View;
	float4x4 Projection;
	float4 EyePosWorld;
};

struct perShadow
{
	float4x4 ShadowView;
	float4x4 ShadowProjection;
	float4x4 pad1;
	float4x4 pad2;
};

Texture2D shadowMap[] : register(t0);

SamplerComparisonState aSampler : register(s2);

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

void CalcShadowFactor(
	float4 shadowPos,
	Texture2D  map,
	out float factor
	)
{
	shadowPos.xyz /= shadowPos.w;

	float depth = shadowPos.z;

	uint width, height, numMips;
	map.GetDimensions(0, width, height, numMips);

	float dx = 1.0f / (float)width;

	float percentLight = 0.0f;
	const int numberOfOffsets = 9;

	const float2 offsets[numberOfOffsets] =
	{
		float2(-dx, -dx), float2(0.0f, -dx), float2 (dx, -dx),
		float2(-dx, 0.0), float2(0.0f, 0.0f), float2(dx, 0.0f),
		float2(-dx, dx), float2(0.0f, dx), float2(dx, dx)
	};

	factor = 0.0f;

	//[unroll]
	for (int i = 0; i < numberOfOffsets; i++)
	{
		factor += map.SampleCmpLevelZero(aSampler, shadowPos.xy + offsets[i], depth).r;
	}

	factor /= 9.0f;
	
}

// Directional Light Computation
void ComputeDirectionalLight(
	Material mat,
	DirectionalLight DirLit,
	float4 normal,
	float4 DirToEye,
	float4 shadowPos,
	float4x4 WorldInv,
	Texture2D map,
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
	float3 L = normalize(mul(-DirLit.Direction, WorldInv).xyz);

	PhongModel(mat, DirLit.LightInt, L, normal.xyz, DirToEye.xyz, ambient, diffuse, spec);

	//---------------------------------
	//	Shadow Stuff
	//---------------------------------

	float shadowMapDepth = map.SampleCmpLevelZero(aSampler, shadowPos.xy, shadowPos.z).r;
	
	float factor = 1.0f;
	
	if (shadowMapDepth <= 1.0f)
	{
		CalcShadowFactor(shadowPos, map, factor);
	}
	
	diffuse *= factor;
	spec *= factor;
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
	float4 shadowPos,
	float4x4 WorldInv,
	Texture2D map,
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

	 //Now we attenuate based on range
	float att = 1 / dot(SptLight.Attenuation.xyz, float3(1, d, d * d));
	
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

	//shadowPos.xyz = shadowPos.xyz / shadowPos.w;

	//float shadowMapDepth = shadowMap[lightIndex].SampleCmpLevelZero(aSampler, shadowPos.xy, shadowPos.z).r;
	
	float factor = 1.0f;
	
	//if (shadowMapDepth <= 1.0f)
	//{
	CalcShadowFactor(shadowPos, map, factor);
	//}
	
	diffuse *= factor;
	spec *= factor;
}

ConstantBuffer<perFrame> Data_PerFrame : register(b0);

ConstantBuffer<perShadow> Data_Shadow[] : register(b1);


// ******* Shader operations

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 PosMS : POSITION;
	float4 ShadowPos[8] : SHADOW_POS;
	float4 Norm : NORMAL;
	float4x4 WorldInv : INSTANCE_WORLDINVERSE;
	Material mat : INSTNACE_MATERIAL;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(float4 Pos : POSITION, float4 nor : NORMAL, float4x4 world : INSTANCE_WORLD, float4x4 worldInv : INSTANCE_WORLDINVERSE, Material mat : INSTANCE_MATERIAL)
{
	VS_OUTPUT output;
	output.PosMS = Pos;  // We pass along the raw model space position 
	output.Norm = nor;	 // and the face normal
	
	output.Pos = mul(Pos, world);
	output.Pos = mul(output.Pos, Data_PerFrame.View);
	output.Pos = mul(output.Pos, Data_PerFrame.Projection);
	


	float4x4 NDCtoTex = {
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f,
	}; 

	float4 worldPos = mul(Pos, world);

	//[unroll]
	for (int i = 0; i < 8; i++) 
	{
		output.ShadowPos[i] = mul(worldPos, Data_Shadow[i].ShadowView);
		output.ShadowPos[i] = mul(output.ShadowPos[i], Data_Shadow[i].ShadowProjection);
		output.ShadowPos[i] = mul(output.ShadowPos[i], NDCtoTex);
	}

	output.WorldInv = worldInv;
	output.mat = mat;


	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
	const int numDirecs = 3;
	int numPoints = 10;
	int numSpots = 5;


	// Compute light values in model-space
		float4 msEyePos = mul(Data_PerFrame.EyePosWorld, input.WorldInv);
		float4 msDirToEye = normalize(msEyePos - input.PosMS);

		float4 ambient = float4(0, 0, 0, 1);
		float4 diffuse = float4(0, 0, 0, 1);
		float4 spec = float4(0, 0, 0, 1);

		float4 A, D, S;

		[unroll]
		for (int i = 0; i < numDirecs; i++) {
			ComputeDirectionalLight(input.mat, Data_PerFrame.DirLight[i], normalize(input.Norm), msDirToEye, input.ShadowPos[i], input.WorldInv, shadowMap[i], A, D, S);

			ambient += A;
			diffuse += D;
			spec += S;
		}

		//for (int i = 0; i < numPoints; i++) {
		//	ComputePointLight(input.mat, Data_PerFrame.PntLightList[i], input.PosMS, normalize(input.Norm), msDirToEye,input.WorldInv, A, D, S);
		//
		//	ambient += A;
		//	diffuse += D;
		//	spec += S;
		//}
	   //
		//ComputeSpotLight(input.mat, Data_PerFrame.SptLightList[0], input.PosMS, normalize(input.Norm), msDirToEye, input.ShadowPos[0 + numDirecs], input.WorldInv, shadowMap[0 + numDirecs], A, D, S);
		//
		//ambient += A;
		//diffuse += D;
		//spec += S;
		//
		//ComputeSpotLight(input.mat, Data_PerFrame.SptLightList[1], input.PosMS, normalize(input.Norm), msDirToEye, input.ShadowPos[1 + numDirecs], input.WorldInv, shadowMap[1 + numDirecs], A, D, S);
		//
		//ambient += A;
		//diffuse += D;
		//spec += S;
	   //


		//Texture2D maps[3] = { shadowMap[3], shadowMap[4], shadowMap[5] };
	
		[unroll]
		for (int p = 0; p < numSpots; p++) {

			ComputeSpotLight(input.mat, Data_PerFrame.SptLightList[p], input.PosMS, normalize(input.Norm), msDirToEye, input.ShadowPos[p+3], input.WorldInv, shadowMap[p + 3], A, D, S);
		
			ambient += A;
			diffuse += D;
			spec += S;
		}

		float4 litColor = ambient + diffuse + spec;

		return litColor;
}
