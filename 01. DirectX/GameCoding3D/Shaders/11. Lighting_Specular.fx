#include "00. Global.fx"

float3 LightDir;
float4 LightSpecular; //specular color
float4 MaterialSpecular;

Texture2D DiffuseMap;

MeshOutput VS(VertexTextureNormal input)
{
	MeshOutput output;
	output.position = mul(input.position, W);
	output.worldPosition = input.position;
	output.position = mul(output.position, VP);
	output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);

	return output;
}

// Specular (반사광)
// 한 방향으로 완전히 반사되는 빛 (Phong)
float4 PS(MeshOutput input) : SV_TARGET
{
	//빛의 반대 방향으로 반사되는 것
	//float3 R = reflect(LightDir, input.normal);
	float3 R = LightDir - (2 * input.normal * dot(LightDir, input.normal));
	R = normalize(R);

	float3 cameraPosition = -V._41_42_43;
	float3 E = normalize(cameraPosition - input.worldPosition);
	float value = saturate(dot(R, E)); //clamp(0~1) 사이로 지정
	float specular = pow(value, 10);

	float4 color = LightSpecular * MaterialSpecular * specular;

	return color;
}

//계층 구조 : 셰이더 ->테크닉 -> 패스
technique11 T0
{
	PASS_VP(p0, VS, PS)
};