//�ߺ� define ����
#ifndef _GLOBAL_FX_
#define _GLOBAL_FX_

// >> : Const Buffer
cbuffer GlobalBuffer
{
	matrix V;		// View
	matrix P;		// Projection
	matrix VP;	// View * Projection
	matrix VInv;
};

cbuffer TransformBuffer
{
	matrix W;		// World
};
// << : Const Buffer

 // >> : VertexData
struct Vertex
{
	float4 position : POSITION;
};
struct VertexTexture
{
	float4 position : POSITION;
	float2 uv : TEXCOORD;
};
struct VertexColor
{
	float4 position : POSITION;
	float2 color : COLOR;
};
struct VertexTextureNormal
{
	float4 position : POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
};

struct VertexTextureNormalTangent
{
	float4 position : POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
};
// << : VertexData

// >> : VertexOutput
struct VertexOutput
{
	float4 position : SV_POSITION; //SV : SystemValue
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
};
struct MeshOutput
{
	float4 position : SV_POSITION; //SV : SystemValue
	float3 worldPosition : POSITION1; // ������� ������ �� �ʿ�
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
};
// << : VertexOutput

// >> : Sampler State
SamplerState LinearSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

SamplerState PointSampler
{
	Filter = MIN_MAG_MIP_POINT;
	AddressU = Wrap;
	AddressV = Wrap;
};
// << : Sampler State

// >> : Rasterizer State
RasterizerState FillModeWireFrame
{
	FillMode = WireFrame;
};
// << : Rasterizer State

// >> : Macro
#define PASS_VP(name, vs, ps)									\
pass name																	\
{																					\
	SetVertexShader(CompileShader(vs_5_0, vs()));		\
	SetPixelShader(CompileShader(ps_5_0, ps()));			\
}

#define PASS_RS_VP(name, rs, vs, ps)							\
pass name																	\
{																					\
    SetRasterizerState(rs);												\
    SetVertexShader(CompileShader(vs_5_0, vs()));		\
    SetPixelShader(CompileShader(ps_5_0, ps()));			\
}

// << : Macro

// >> : Functions
float3 CameraPosition()
{	
	return VInv._41_42_43;
}
// << : Functions

#endif