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
	(input.position)이 원점을 중심으로 하는 가정하에
	sky sphere은 카메라(view)를 기준으로 따라다니기 때문에 굳이 world를 곱해줄 필요 없다.
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
