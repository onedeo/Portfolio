#include "00. Global.fx"

float4 MaterialEmissive;

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

// Emissive
// ī�޶�� ��ü���� �ۿ�
// �ܰ����� ���� �� ���
// (������Ʈ)
float4 PS(MeshOutput input) : SV_TARGET
{
	float3 cameraPostion = -V._41_42_43;
	float3 E = normalize(cameraPostion - input.worldPosition);

	float value = saturate(dot(E, input.normal));
	float emissive = 1.0f - value;

	// min, max, x ������ �ε巴�� �������ִ� �Լ� : smoothstep
	emissive = smoothstep(0.0f, 1.0f, emissive);
	emissive = pow(emissive, 3);
	float4 color = MaterialEmissive * emissive;

	return color;
}

//���� ���� : ���̴� ->��ũ�� -> �н�
technique11 T0
{
	PASS_VP(p0, VS, PS)
};