#pragma once

#include "Viewport.h"

class Graphics
{
	DECLARE_SINGLE(Graphics);

public:
	void Init(HWND hwnd);

	void RenderBegin();
	void RenderEnd();

	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; }

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void CreateDepthStencilView();

public:
	void SetViewport(float width, float height, float x = 0, float y = 0, float minDepth = 0, float maxDepth = 1);
	Viewport& GetViewport() { return _vp; }

private:
	HWND _hwnd = {};

	// Device & SwapChain
	ComPtr<ID3D11Device> _device = nullptr;								//물체를 찍어낸다
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;		//물체 리소스를 파이프라인에 바인딩
	ComPtr<IDXGISwapChain> _swapChain = nullptr;						//전/후면버퍼 더블버퍼링

	// RTV
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	// DSV
	ComPtr<ID3D11Texture2D> _depthStencilTexture;
	ComPtr<ID3D11DepthStencilView> _depthStencilView;

	// Misc
	Viewport _vp;
};

