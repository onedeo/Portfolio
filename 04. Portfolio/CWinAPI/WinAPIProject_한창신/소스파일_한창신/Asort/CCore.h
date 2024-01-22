#pragma once
#include "pch.h"

class CCore
{
public:
	SINGLE(CCore);

private:
	HWND			hWnd;					// ���� ������ �ڵ�
	Point			ptResolution;		// ���� ������ �ػ�
	HDC				hDC;					// HDC

	//double buffering
	HBITMAP		hBit;
	HDC				memDC;

	//���� ����ϴ� GDI Object
	HBRUSH arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN arrPen[(UINT)PEN_TYPE::END];

	//Ocuppied Area
	RECT rectOCDTotalSize;
	int iStage;

	bool bCleared;

public:
	int init(HWND _hWnd, Point _ptResolution);
	void Progress();
	HDC getMainDC() { return hDC; }
	HWND get_MainHwnd();
	Point get_Resolution() { return ptResolution; }
	bool GetCleared(){return bCleared;}
	void SetCleared(bool _cleared) { bCleared = _cleared; }
	int GetStage() { return iStage; }

	HBRUSH getBrush(BRUSH_TYPE _eType) {return arrBrush[(UINT)_eType]; }
	HPEN getPen(PEN_TYPE _eType) { return arrPen[(UINT)_eType]; }

	////Ocuppied Area
	RECT GetOCDTotalSize(){ return rectOCDTotalSize; }

private:
	void CreateBrushPen();
	
private:
	void Update();
	void Render();
};