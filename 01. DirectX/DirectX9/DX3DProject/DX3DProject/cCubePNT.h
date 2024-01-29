#pragma once

class cCubePNT
{
public:
	cCubePNT();
	virtual ~cCubePNT(void);

	virtual void Setup();
	virtual void Update();
	virtual void Render();

protected:
	std::vector<ST_PNT_VERTEX>  m_vecVertex;

};

