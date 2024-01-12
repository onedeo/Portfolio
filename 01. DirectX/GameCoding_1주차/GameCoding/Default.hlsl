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
	row_major matrix matWorld;
}

cbuffer CameraData : register(b1)
{
	//ī�޶� �ǳ��ִ� ��� ���������� �ѹ���
	row_major matrix matView;
	row_major matrix matProjection;
	// matView�� matProjection�� ī�޶�� '��' ������ ����
	// camera buffer�� ����� ���� ���ָ� �ȴ� (�ѹ��� �ϸ� ��)
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

	float4 position = mul(input.position, matWorld); //World
	position = mul(position, matView); //View
	position = mul(position, matProjection); //Projection 

	output.position = position;
	//output.color = input.color;
	output.uv= input.uv;

	return output;
}

Texture2D texture0 : register(t0); // ������ �԰ݿ� ���� �̸� ���ϴ� ��
SamplerState sampler0 : register(s0);

//RS -> �ﰢ�� �ȿ� �ִ� ������ �ɷ��ִ� ���� -> PS�� �Ѱ���
float4 PS(VS_OUTPUT input) : SV_Target // ����� ���õ� �Լ�
{
	float4 color = texture0.Sample(sampler0, input.uv);
	
	return color;
}