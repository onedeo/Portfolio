#include "00. Global.fx"

float4 LightAmbient;			// ������ ambient ȿ�� (���� ��ü�� ����)
float4 MaterialAmbient;		// ��ü�� ����

VertexOutput VS(VertexTextureNormal input)
{
	VertexOutput output;
	output.position = mul(input.position, W);
	output.position = mul(output.position, VP);

	output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);

	return output;
}

Texture2D Texture0;

//Ambient (�ֺ���, ȯ�汤)
// ������ �ݻ縦 ���� ������ �Һи��� ��
//������ ���� ������ ǥ��

float4 PS(VertexOutput input) : SV_TARGET
{
	float4 color = LightAmbient * MaterialAmbient;
	return Texture0.Sample(LinearSampler, input.uv) * color;
}

technique11 T0
{
	PASS_VP(p0, VS, PS)
};