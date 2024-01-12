/*
* 
HLSL�� High-Level Shading Language�� ���ڷ�, �׷��� ���ø����̼ǿ��� GPU(�׷��� ó�� ��ġ)���� ����Ǵ� ���̴�(Shader) ���α׷��� �ۼ��ϴ� �� ���Ǵ� ���α׷��� ���

	shader ��� ���
		- ����� ������� �ε��ϴ� ���
		- �������� ������� ����� �ε��ϴ� ���
*/

struct VS_INPUT
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};


//VertexShader �ܰ� (IA->VS->RS->PS->OM)
VS_OUTPUT  main(VS_INPUT input) //vertex ���� ���� -> ��ġ�� ���õ� �Լ�
{
	VS_OUTPUT output;
	output.position = input.position;
	output.color = input.color;

	return output;
}

//RS -> �ﰢ�� �ȿ� �ִ� ������ �ɷ��ִ� ���� -> PS�� �Ѱ���
float4 PS(VS_OUTPUT input) : SV_Target // ����� ���õ� �Լ�
{

	return input.color;
}