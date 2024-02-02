#include "00. Global.fx"
#include "00. Light.fx"

struct VS_OUT
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

VS_OUT VS(VertexTextureNormalTangent input)
{
	VS_OUT output;
	/*
	(input.position)�� ������ �߽����� �ϴ� �����Ͽ�
	sky sphere�� ī�޶�(view)�� �������� ����ٴϱ� ������ ���� world�� ������ �ʿ� ����.
	*/

	// local -> world -> view ->projection
	float4 viewPos = mul(float4(input.position.xyz, 0), V);
	float4 clipPos = mul(viewPos, P);

	output.position = clipPos.xyzw;
	output.position.z = output.position.w * 0.9999999f;

	output.uv = input.uv;

	// xyzw

	return output;
}

float4 PS(VS_OUT input) : SV_TARGET
{
	float4 color = DiffuseMap.Sample(LinearSampler, input.uv);

	return color;
}

float4 PS_RED(MeshOutput input) : SV_TARGET
{
	return float4(1, 0, 0, 1);
}

technique11 T0
{
	pass P0
	{
		SetRasterizerState(FrontCounterClockwiseTrue);
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
};
