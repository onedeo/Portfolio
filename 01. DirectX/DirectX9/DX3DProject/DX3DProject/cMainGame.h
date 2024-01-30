#pragma once

class cCamera;
class cCubePC;
class cGrid;
class cCubeMan;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Setup_Line();
	void Draw_Line();

	void Setup_Triangle();
	void Draw_Triangle();

	void Setup_Light();

	// Texture
	void Setup_Texture();
	void Draw_Texture();
	/*
		함수를 기능적으로 구분하는것은 유지보수에 좋다 
		하지만 함수를 호출하는데 있어 함수의 주소값 만큼의 메모리를 차지한다
		이를 방지하기 위해 inline을 사용할 수 있지만 inline을 사용하면 코드가 길어져 실행파일이 커진다
	*/

private:
	std::vector<ST_PC_VERTEX>		m_vecLineVertex;
	std::vector<ST_PC_VERTEX>		m_vecTriangleVertex;

	cCamera* m_pCamera;
	cCubePC* m_pCubePC;
	cGrid* m_pGrid;
	cCubeMan* m_pCubeMan;

	// Texture
	LPDIRECT3DTEXTURE9			m_pTexture;
	std::vector<ST_PT_VERTEX>	m_vecTexVertex;
};

