#pragma once
class VertexBuffer
{
public:
	VertexBuffer(ComPtr<ID3D11Device> device);
	~VertexBuffer();

	template<typename T>
	void Create(const vector<T>& vertices)
	{
		_stride = sizeof(T); //T�� ũ��
		_count = static_cast<uint32>(vertices.size());

		D3D11_BUFFER_DESC desc; // ���� ���� : GPU ���ۿ� ������ �� �ֵ��� ����
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		//GPU�� ReadOnly�����ͷ� �ȴٴ� ��. �ٸ� �͵鵵 ã�ƺ���
		/*
		�� readonly�ΰ�? ĳ���ʹ� �������Ĵ�
		��� ��ü�� �ٲ��� �ʱ� ����. ����� ������� ���� ������ �ʰ� ��ġ(��ǥ)�� ���Ѵ� -> offset���� ����
		�������� ������ �������� �ʰ� offset�� �����Ͽ� ��ġ ����
		*/
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = (uint32)(_stride * _count);

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vertices.data(); // ù��° �������� ���� �ּ� = &_vertices = _vertices.data()

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
[CPU<->RAM] : CPU ���� <-> [GPU<->VRAM] : GPU ����
GPU���� ������ ������ �������� �Ѵ� :VertexBuffer
*/
};

