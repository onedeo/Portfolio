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

cbuffer CameraData : register(b0)
{
	//ī�޶� �ǳ��ִ� ��� ���������� �ѹ���
	row_major matrix matView;
	row_major matrix matProjection;
	// matView�� matProjection�� ī�޶�� '��' ������ ����
	// camera buffer�� ����� ���� ���ָ� �ȴ� (�ѹ��� �ϸ� ��)
}

cbuffer TransformData : register(b1)
{
	row_major matrix matWorld;
}

cbuffer AnimationData : register(b2)
{
	float2 spriteOffset;
	float2 spriteSize;
	float2 textureSize;
	float useAnimation;
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
	output.uv= input.uv;

	if (useAnimation == 1.0f)
	{
		output.uv *= spriteSize / textureSize;
		output.uv += spriteOffset / textureSize;
	}

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