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
	//D3DFVF_TEX1�� �ؽ��ĸ� � ���ĸ� �����ϴ� ������ ���� ������ �ε巴�� ǥ���� �� ������ ���ϰ� �ɸ���
};