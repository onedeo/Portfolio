#pragma once

class cGizmo
{
public:
	cGizmo();
	~cGizmo();

	void Setup(D3DCOLOR color, D3DXMATRIXA16& matrix);
	void Render();

private:
	std::vector<ST_PC_VERTEX> m_vecVertex;
	D3DXMATRIXA16 m_matRotation;

};