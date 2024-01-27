#pragma once

class cCamera;
class cCubePC;
class cGrid;

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
	cGrid* m_pGrid;

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

