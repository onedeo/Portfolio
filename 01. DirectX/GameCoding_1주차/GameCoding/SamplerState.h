#pragma once
class SamplerState
{	// texture�� ���� �� ����� ��� �Ұ����� : ����� ������� ���Ѱ���, ����� texutre �ݺ��Ұ���, �ſ�� �Ұ��� ��
	// min mag ���� : ��ü�� �׷����� �������� �۰� ǥ�õɶ� ��� �Ұ���, �������� Ŀ�� �� ��� �Ұ���
public:
	SamplerState(ComPtr<ID3D11Device> device);
	~SamplerState();

	ComPtr<ID3D11SamplerState> GetComPtr() { return _samplerState; }

	void Create();

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11SamplerState> _samplerState;
};

