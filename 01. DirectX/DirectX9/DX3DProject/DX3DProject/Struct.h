#pragma once
#include "framework.h"

struct ST_PC_VERTEX
{
	D3DXVECTOR3		p;
	D3DCOLOR				c;
	enum { FVF = D3DFVF_XYZ|D3DFVF_DIFFUSE };
};
