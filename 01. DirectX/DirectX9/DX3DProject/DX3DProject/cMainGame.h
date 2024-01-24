#pragma once
#include "cCubePC.h"
#include "cCamera.h"

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	std::vector<ST_PC_VERTEX>		m_vecLineVertex;
	std::vector<ST_PC_VERTEX>		m_vecTriangleVertex;

	cCamera* m_pCamera;
	cCubePC* m_pCubePC;

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Setup_Line();
	void Draw_Line();

	void Setup_Triangle();
	void Draw_Triangle();

};

