#include "00. Global.fx"

float3 LightDir;
float4 LightDiffuse;
float4 MaterialDiffuse;
Texture2D DiffuseMap;

VertexOutput VS(VertexTextureNormal input)
{
	VertexOutput output;
	output.position = mul(input.position, W);
	output.position = mul(output.position, VP);

	output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);

	return output;
}

// Diffuse
// 물체의 표면에서 분산되어 눈으로 바로 들어오는 빛
// 각도에 따라 밝기가 다르다 (Lambert공식 (내적 이용))
float4 PS(VertexOutput input) : SV_TARGET
{
	float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
	float value = dot(-LightDir, normalize(input.normal));

	color = color * value * LightDiffuse * MaterialDiffuse;

	return color;
}

//계층 구조 : 셰이더 ->테크닉 -> 패스
technique11 T0
{
	PASS_VP(p0, VS, PS)
};