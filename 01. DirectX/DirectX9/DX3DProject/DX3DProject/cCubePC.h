#pragma once
class cCubePC
{
public:
	cCubePC();
	~cCubePC();

	void Setup();
	void Update();
	void Render();

	D3DXVECTOR3& GetPosition() { return m_vPosition; }

private:
	std::vector<ST_PC_VERTEX> m_vecVertex;

	D3DXVECTOR3			m_vDirection;
	D3DXVECTOR3			m_vPosition;
	D3DXMATRIXA16		m_matWorld;
	float			m_fRotY;

};

