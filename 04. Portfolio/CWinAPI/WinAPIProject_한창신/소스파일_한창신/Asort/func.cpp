#include "func.h"
#include "CEventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eType)
{
	tEvent event = {};
	event.eEvent = EVENT_TYPE::CREATE_OBJECT;
	event.lParam = (DWORD_PTR)_pObj;
	event.wParam = (DWORD_PTR)_eType;

	CEventMgr::GetInst()->AddEvent(event);
}

void myDeleteObject(CObject* _pObj, GROUP_TYPE _eType)
{
	tEvent event = {};
	event.eEvent = EVENT_TYPE::DELETE_OBJECT;
	event.lParam = (DWORD_PTR)_pObj;

	CEventMgr::GetInst()->AddEvent(event);
}

void ChangeScene(SCENE_TYPE _nxt)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_nxt;

	CEventMgr::GetInst()->AddEvent(evn);
}

float GetDistance(Vec2 p1, Vec2 p2)
{
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;
	return  sqrt(x * x + y * y);
}

bool IsBetweenTwo(int p1, int p2, int target)
{
	if (p1 > p2)
	{
		if (target > p2 && target < p1)
			return true;
	}
	else
	{
		if (target > p1 && target < p2)
			return true;
	}

	return false;
}

bool IsBetweenX(Vec2 v1, Vec2 v2, Vec2 target)
{
//	if (v1.y != v2.y) return false;
		
	if (v1.x > v2.x)
	{
		if (target.x > v2.x && target.x < v1.x)
			return true;
	}
	else
	{
		if (target.x > v1.x && target.x < v2.x)
			return true;
	}

	return false;
}
bool IsBetweenY(Vec2 v1, Vec2 v2, Vec2 target)
{
	//if (v1.x != v2.x) return false;
	//else if (v1.x != target.x) return false;

	if (v1.y > v2.y)
	{
		if (target.y >= v2.y && target.y <= v1.y)
			return true;
	}
	else
	{
		if (target.y >= v1.y && target.y <= v2.y)
			return true;
	}
	
	return false;
}
bool IsBetweenXorY(Vec2 v1, Vec2 v2, Vec2 target)
{
	if (IsBetweenX(v1, v2, target) || IsBetweenY(v1, v2, target))
		return true;
	else return false;
}

bool IsBetweenX(Point p1, Point p2, Vec2 target)
{
	//if (p1.y != p2.y) return false;
	target = Vec2(target.ToPoint());
	if (p1.x > p2.x)
	{
		if (target.x > p2.x && target.x < p1.x)
			return true;
	}
	else
	{ 
		if (target.x > p1.x && target.x < p2.x)
			return true;
	}

	return false;
}
bool IsBetweenY(Point p1, Point p2, Vec2 target)
{
	//if (p1.x != p2.x) return false;
	target = Vec2(target.ToPoint());

	if (p1.y > p2.y)
	{
		if (target.y > p2.y && target.y < p1.y)
			return true;
	}
	else
	{
		if (target.y > p1.y && target.y < p2.y)
			return true;
	}

	return false;
}
bool IsBetweenXorY(Point p1, Point p2, Vec2 target)
{
	return (IsBetweenX(p1, p2, target) || IsBetweenY(p1, p2, target));
}

bool IsOnXAxis(Point p1, Point p2, Vec2 target)
{
	if (!IsBetweenX(p1, p2, target)) return false;
	if (p1.y != target.y) return false;

	return true;
}
bool IsOnYAxis(Point p1, Point p2, Vec2 target)
{
	if (!IsBetweenY(p1, p2, target)) return false;
	if (p1.x != target.x) return false;

	return true;
}
bool IsOnXorYAxis(Point p1, Point p2, Vec2 target)
{
	if (p1.AroundEqual(target.ToPoint()) || p2.AroundEqual(target.ToPoint())) return true;

	return IsOnXAxis(p1, p2, target) || IsOnYAxis(p1, p2, target);
}

int CountLinesOnDirection(Vec2 _pos, OCDPoint* _ocdPoint, DIRECTION _dir)
{
	int count = 0;
	OCDPoint* i = _ocdPoint;
	do
	{
		switch (_dir)
		{
			case DIRECTION::RIGHT:
			{
				if (_pos.x < i->pPoint.x)
				{
					if (IsBetweenY(i->pPoint, i->nxt->pPoint, _pos))
						count++;
				}
			}
			break;
			case DIRECTION::LEFT:
			{
				if (_pos.x > i->pPoint.x)
				{
					if (IsBetweenY(i->pPoint, i->nxt->pPoint, _pos))
						count++;
				}
			}
			break;
			case DIRECTION::UP:
			{
				if (_pos.y > i->pPoint.y)
				{
					if (IsBetweenX(i->pPoint, i->nxt->pPoint, _pos))
						count++;
				}
			}
			break;
			case DIRECTION::DOWN:
			{
				if (_pos.y < i->pPoint.y)
				{
					if (IsBetweenX(i->pPoint, i->nxt->pPoint, _pos))
						count++;
				}
			}
			break;
		}
		i = i->nxt;
	} while (i != _ocdPoint);

	return count;
}
int CountLinesOnDirection(Point _pCen, OCDPoint* _ocdPoint, DIRECTION _dir)
{
	int count = 0;
	OCDPoint* i = _ocdPoint;
	do
	{
		switch (_dir)
		{
			case DIRECTION::RIGHT:
			{
				if (_pCen.x < i->pPoint.x)
				{
					if (IsBetweenY(i->pPoint, i->nxt->pPoint, _pCen))
						count++;
				}
			}
			break;
			case DIRECTION::LEFT:
			{
				if (_pCen.x > i->pPoint.x)
				{
					if (IsBetweenY(i->pPoint, i->nxt->pPoint, _pCen))
						count++;
				}
			}
			break;
			case DIRECTION::UP:
			{
				if (_pCen.y > i->pPoint.y)
				{
					if (IsBetweenX(i->pPoint, i->nxt->pPoint, _pCen))
						count++;
				}
			}
			break;
			case DIRECTION::DOWN:
			{
				if (_pCen.y < i->pPoint.y)
				{
					if (IsBetweenX(i->pPoint, i->nxt->pPoint, _pCen))
						count++;
				}
			}
			break;
		}
		i = i->nxt;
	} while (i != _ocdPoint);

	return count;


}