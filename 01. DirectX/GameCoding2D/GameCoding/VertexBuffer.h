#pragma once
class VertexBuffer
{
public:
	VertexBuffer(ComPtr<ID3D11Device> device);
	~VertexBuffer();

	template<typename T>
	void Create(const vector<T>& vertices)
	{
		_stride = sizeof(T); //T의 크기
		_count = static_cast<uint32>(vertices.size());

		D3D11_BUFFER_DESC desc; // 버퍼 생성 : GPU 버퍼에 저장할 수 있도록 설정
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		//GPU가 ReadOnly데이터로 된다는 것. 다른 것들도 찾아볼것
		/*
		왜 readonly인가? 캐릭터는 움직일탠대
		모양 자체가 바뀌지 않기 때문. 사과를 만들어질 때는 변하지 않고 위치(좌표)만 변한다 -> offset으로 조정
		기하학적 도형을 수정하지 않고 offset을 조정하여 위치 조정
		*/
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = (uint32)(_stride * _count);

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vertices.data(); // 첫번째 데이터의 시작 주소 = &_vertices = _vertices.data()

		HRESULT hr = _device->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
		CHECK(hr);
	}

	ComPtr<ID3D11Buffer> GetComPtr() { return _vertexBuffer; }
	uint32 GetStride() { return _stride; }
	uint32 GetOffset() { return _offset; }
	uint32 GetCount() { return _count; }

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11Buffer> _vertexBuffer;

	uint32 _stride = 0;
	uint32 _offset = 0;
	uint32 _count = 0;

	/*
[CPU<->RAM] : CPU 영역 <-> [GPU<->VRAM] : GPU 영역
GPU에도 동일한 정보를 만들어줘야 한다 :VertexBuffer
*/
};

