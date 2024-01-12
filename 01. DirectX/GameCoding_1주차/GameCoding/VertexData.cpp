#include "pch.h"
#include "VertexData.h"

vector<D3D11_INPUT_ELEMENT_DESC> VertexTextureData::descs =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//12 : 첫 번째에서 부터 12번째 이후로 COLOR이 시작된다는 의미(POSITION은 R32,G32,B32로 각 4바이트씩 12바이트로 이후에 러가시작된다고 보면됨
	//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//D3D11_APPEND_ALIGNED_ELEMENT 위 내용을 자동으로 계산해준다
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

vector<D3D11_INPUT_ELEMENT_DESC> VertexColorData::descs =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//12 : 첫 번째에서 부터 12번째 이후로 COLOR이 시작된다는 의미(POSITION은 R32,G32,B32로 각 4바이트씩 12바이트로 이후에 러가시작된다고 보면됨
	//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//D3D11_APPEND_ALIGNED_ELEMENT 위 내용을 자동으로 계산해준다
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};