matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;
float3 LightDir;
//전역 변수라는 개념이 아니라 글로버 버퍼에 있는 것이다



struct VertexInput
{ 
	float4 position : POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
};

struct VertexOutput
{
	float4 position : SV_POSITION; //SV : SystemValue
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;
	output.position = mul(input.position, World);
	output.position = mul(output.position, View);
	output.position = mul(output.position, Projection);

	output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)World);

	return output;
}

SamplerState Sampler0
{
	AddressU = Wrap;
	AddressV = Wrap;
};

float4 PS(VertexOutput input) : SV_TARGET
{
	float3 normal = normalize(input.normal);
	float3 light = -LightDir;

	//return float4(1, 1, 1, 1) * dot(light, normal);

	return Texture0.Sample(Sampler0, input.uv) * dot(light, normal);
}
RasterizerState FillModeWireFrame
{
	FillMode = Wireframe;
};

//계층 구조 : 셰이더 ->테크닉 -> 패스
technique11 T0
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
	pass P1
	{
		SetRasterizerState(FillModeWireFrame);
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
};