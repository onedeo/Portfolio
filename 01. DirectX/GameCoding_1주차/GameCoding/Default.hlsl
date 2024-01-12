/*
HLSL은 High-Level Shading Language의 약자로, 그래픽 애플리케이션에서 GPU(그래픽 처리 장치)에서 실행되는 셰이더(Shader) 프로그램을 작성하는 데 사용되는 프로그래밍 언어

	shader 사용 방법
		- 빌드된 결과물을 로드하는 방법
		- 동적으로 결과물을 만들고 로드하는 방법
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
	//카메라가 건내주는 뷰랑 프로젝션은 한번만
	row_major matrix matView;
	row_major matrix matProjection;
	// matView와 matProjection은 카메라와 '만' 관련이 있음
	// camera buffer을 만들어 따로 빼주면 된다 (한번만 하면 됨)
}

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	//float4 color : COLOR;
	float2 uv : TEXCOORD;
};

// IA - VS - RS - PS - OM
VS_OUTPUT VS(VS_INPUT input) //vertex 단위 실행 -> 위치와 관련된 함수
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

Texture2D texture0 : register(t0); // 정해진 규격에 따라 이름 정하는 것
SamplerState sampler0 : register(s0);

//RS -> 삼각형 안에 있는 영역만 걸러주는 역할 -> PS로 넘겨줌
float4 PS(VS_OUTPUT input) : SV_Target // 색상과 관련된 함수
{
	float4 color = texture0.Sample(sampler0, input.uv);
	
	return color;
}