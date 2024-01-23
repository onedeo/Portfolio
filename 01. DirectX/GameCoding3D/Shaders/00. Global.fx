//중복 define 방지
#ifndef _GLOBAL_FX_
#define _GLOBAL_FX

// >> : Const Buffer
cbuffer GlobalBuffer
{
	matrix V;		// View
	matrix P;		// Projection
	matrix VP;	// View * Projection
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
// << : VertexData

// >> : VertexOutput
struct VertexOutput
{
	float4 position : SV_POSITION; //SV : SystemValue
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
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
// << : Macro

// >> : Functions

// << : Functions

#endif
