#pragma once

struct PipelineInfo
{
	shared_ptr<InputLayout> inputLayout;
	shared_ptr<VertexShader> vertexShader;
	shared_ptr<PixelShader> pixelShader;
	shared_ptr<RasterizerState> rasterizerState;
	shared_ptr<BlendState> blendState;
	D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

class Pipeline
{	//gameobject가 ia, vs, ps 등 정보를 그려달라고 요청하는 곳이라고 생각하면 됨
	//device context가 핵심. devicecontext와 자원을 매핑해주는 역할
public:
	Pipeline(ComPtr<ID3D11DeviceContext> deviceContext);
	~Pipeline();

	void UpdatePipeline(PipelineInfo info); //꼭 필요한 애들로 구성

	// 필요한 애들이 사용할 수 있도록 따로 빼놓음
	void SetVertexBuffer(shared_ptr<VertexBuffer> buffer);
	void SetIndexBuffer(shared_ptr<IndexBuffer> buffer);

	template<typename T>
	void SetConstantBuffer(uint32 slot, uint32 scope, shared_ptr<ConstantBuffer<T>> buffer)
	{
		if(scope & SS_VertexShader)
		_deviceContext->VSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());

		if (scope & SS_PixelShader)
			_deviceContext->PSSetConstantBuffers(slot, 1, buffer->GetComPtr().GetAddressOf());
	}

	void SetTexture(uint32 slot, uint32 scope, shared_ptr<Texture> texture);
	void SetSamplerState(uint32 slot, uint32 scope, shared_ptr<SamplerState> samplerState);
		
	void Draw(uint32 vertexCount, uint32 startVertexLocation);
	void DrawIndexed(uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation);
	//Draw : 정점만 사용 DrawIndex : Index사용

private:
	ComPtr<ID3D11DeviceContext> _deviceContext;
};

