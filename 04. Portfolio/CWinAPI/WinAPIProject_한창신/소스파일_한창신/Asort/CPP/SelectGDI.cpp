#include "../Header/SelectGDI.h"
#include "../Header/CCore.h"

SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _ePenType)
	:hDC(_dc)
	,hDefaultBrush(nullptr)
{
	HPEN hPen = CCore::GetInst()->getPen(_ePenType);
	hDefaultPen = (HPEN)SelectObject(_dc, hPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _eBrushType)
	:hDC(_dc)
	, hDefaultPen(nullptr)
{
	HBRUSH hBrush = CCore::GetInst()->getBrush(_eBrushType);
	hDefaultBrush = (HBRUSH)SelectObject(_dc, hBrush);
}

SelectGDI::~SelectGDI()
{
	SelectObject(hDC, hDefaultPen);
	SelectObject(hDC, hDefaultBrush);

}
