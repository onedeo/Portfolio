#include "pch.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(ComPtr<ID3D11Device> device)
	:_device(device)
{

}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Create(const vector<uint32>& indices)
{
	_stride = sizeof(uint32);
	_count = static_cast<uint32>(indices.size());

	D3D11_BUFFER_DESC desc; // 버퍼 생성 : GPU 버퍼에 저장할 수 있도록 설정
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_IMMUTABLE; //GPU가 ReadOnly데이터로 된다는 것. 다른 것들도 찾아볼것
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = (uint32)(sizeof(uint32) * indices.size());

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = indices.data(); // 첫번째 데이터의 시작 주소 = &_vertices = _vertices.data()

	HRESULT hr =_device->CreateBuffer(&desc, &data, _indexBuffer.GetAddressOf());
	CHECK(hr);
}
