#pragma once
#include "pch.h"


class SelectGDI
{
private:
	HDC hDC;
	
	HPEN hDefaultPen;
	HBRUSH hDefaultBrush;





public: 
	SelectGDI(HDC _dc, PEN_TYPE _ePenType);
	SelectGDI(HDC _dc, BRUSH_TYPE _eBrushType);
	~SelectGDI();
};

