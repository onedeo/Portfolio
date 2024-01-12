/*
HLSL�� High-Level Shading Language�� ���ڷ�, �׷��� ���ø����̼ǿ��� GPU(�׷��� ó�� ��ġ)���� ����Ǵ� ���̴�(Shader) ���α׷��� �ۼ��ϴ� �� ���Ǵ� ���α׷��� ���

	shader ��� ���
		- ����� ������� �ε��ϴ� ���
		- �������� ������� ����� �ε��ϴ� ���
*/

struct VS_INPUT
{
	float4 position : POSITION;
	//float4 color : COLOR;
	float2 uv : TEXCOORD;
};

cbuffer TransformData : register(b0)
{
	float4 offset;
}

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	//float4 color : COLOR;
	float2 uv : TEXCOORD;
};

// IA - VS - RS - PS - OM
VS_OUTPUT VS(VS_INPUT input) //vertex ���� ���� -> ��ġ�� ���õ� �Լ�
{
	VS_OUTPUT output;
	output.position = input.position + offset;
	//output.color = input.color;
	output.uv= input.uv;

	return output;
}

Texture2D texture0 : register(t0); // ������ �԰ݿ� ���� �̸� ���ϴ� ��
Texture2D texture1 : register(t1);
SamplerState sampler0 : register(s0);

//RS -> �ﰢ�� �ȿ� �ִ� ������ �ɷ��ִ� ���� -> PS�� �Ѱ���
float4 PS(VS_OUTPUT input) : SV_Target // ����� ���õ� �Լ�
{
	float4 color = texture1.Sample(sampler0, input.uv);
	
	return color;
}