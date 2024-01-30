#include "00. Global.fx"
#include "00. Light.fx"

#define MAX_MODEL_TRANSFORMS 50

cbuffer BoneBuffer
{
	matrix BoneTransforms[MAX_MODEL_TRANSFORMS];
};

uint BoneIndex;

MeshOutput VS(VertexTextureNormalTangent input)
 {
	/*
	- input은 자기 자신의 좌표 기준으로 들어온 모델(world, parent 상대 배치안된상태)
	- BoneTransform은 input의 계층에서 root까지 가는 행렬 (부모가 하나면 부모의 행렬이고, 부모가 2개면 부모x조부모 행렬이다)
	- 그 이후에 WVP를 곱해준다
	*/
	MeshOutput output;
	output.position = mul(input.position, BoneTransforms[BoneIndex]);
	output.position = mul(output.position, W);
	output.worldPosition = output.position.xyz;
	output.position = mul(output.position, VP);
	output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);
	output.tangent = mul(input.tangent, (float3x3)W);

	return output;
 }

float4 PS(MeshOutput input) : SV_TARGET
{
	//ComputeNormalMapping(input.normal, input.tangent, input.uv);

	//float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);

	//return color;
	return DiffuseMap.Sample(LinearSampler, input.uv);
}

float4 PS_RED(MeshOutput input) : SV_TARGET
{
	return float4(1,0,0,1);
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
	PASS_RS_VP(P1, FillModeWireFrame, VS, PS_RED)
};
