#pragma once
#include "framework.h"

struct ST_PC_VERTEX
{
	D3DXVECTOR3		p;
	D3DCOLOR				c;
	enum { FVF = D3DFVF_XYZ|D3DFVF_DIFFUSE };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3		p;
	D3DXVECTOR3		n;
	D3DXVECTOR2		t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
	//D3DFVF_TEX1은 텍스쳐를 몇개 쓰냐를 정의하는 것으로 많이 쓸수록 부드럽게 표현할 수 있지만 부하가 걸린다
};