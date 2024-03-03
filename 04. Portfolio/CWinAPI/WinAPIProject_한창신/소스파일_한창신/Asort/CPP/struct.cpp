#pragma once
#include "../Header/pch.h"
#include "../Header/struct.h"


	Point::Point()
	{
		x = 0, y = 0;
	}
	Point::Point(Vec2 _vec2)
	{
		x = round(_vec2.x);
		y = round(_vec2.y);
	}
	Point::Point(float _x, float _y)
	{
		x = round(_x);
		y = round(_y);
	}
	bool Point::operator==(const Point& _ivec2)
	{
		return x == _ivec2.x && y == _ivec2.y;
	}
	bool Point::operator==(Vec2& _vec2)
	{
		Point temp = _vec2.ToPoint();
		return x == temp.x && y == temp.y;
	}
	bool Point::operator==(Point& _p)
	{
		return x == _p.x && y == _p.y;
	}

	bool Point::AroundEqual(Point p)
	{
		return (abs(x - p.x) <= 1) && (abs(y - p.y) <= 1);
	}

	void  Point::operator=(Vec2& _vec2)
	{
		x = round(_vec2.x);
		y = round(_vec2.y);
	}
	Point&  Point::operator+(Point& _p)
	{
		x += _p.x;
		y += _p.y;

		return *this;
	}
	Point& Point::operator+(Vec2 _vec2)
	{
		Point p = _vec2.ToPoint();
		x += p.x;
		y += p.y;

		return *this;
	}
	Vec2 Point::ToVec2()
	{
		return Vec2((float)x, (float)y);
	}

	float Vec2::Length()
	{
		return sqrt(x * x + y * y);
	}
	Vec2& Vec2::Normalize()
	{
		float fLen = Length();
		if(fLen==0)fLen=1;

		x /= fLen;
		y /= fLen;

		return *this;
	}
	const Point Vec2::ToPoint()
	{
		return Point((int)round(x), (int)round(y));
	}
	void Vec2::operator = (Point _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}
	Vec2& Vec2::operator +(Vec2 _vec2)
	{
		x += _vec2.x;
		y += _vec2.y;

		return *this;
	}
	Vec2& Vec2::operator +(Point _vec2)
	{
		x += _vec2.x;
		y += _vec2.y;

		return *this;
	}
	Vec2& Vec2::operator* (float a)
	{
		x *= a;
		y *= a;
		return *this;
	}
	bool Vec2::operator==(const Vec2& _vec2)
	{
		return x == _vec2.x && y == _vec2.y;
	}
	bool Vec2::operator==(const Point& _ivec2)
	{
		Point temp = ToPoint();
		return _ivec2.x == temp.x && _ivec2.y == temp.y;
	}
	void Vec2::operator=(const Point& _ivec2)
	{
		x = _ivec2.x;
		y = _ivec2.y;
	}
	Vec2::Vec2()
		:x(0.f)
		, y(0.f)
	{}
	Vec2::Vec2(float _x, float _y)
		:x(_x)
		, y(_y)
	{}
	Vec2::Vec2(int _x, int _y)
		:x((float)_x)
		, y((float)_y)
	{}
	Vec2::Vec2(LONG _x, LONG _y)
		:x((float)_x)
		, y((float)_y)
	{}
	Vec2::Vec2(const Point& _pt)
		: x((float)_pt.x),
		y(((float)_pt.y))
	{}
	//Vec2::Vec2(const POINT& _pt)
	//	: x((float)_pt.x),
	//	y(((float)_pt.y))
	//{}
	Vec2::Vec2(float _xy)
		:x(_xy),
		y(_xy)
	{}
	Vec2::Vec2(int _xy)
		:x((float)_xy),
		y((float)_xy)
	{}


	OCDPoint::OCDPoint()
		:pPoint(0, 0)
		, nxt(nullptr)
		, prv(nullptr)
	{}
	OCDPoint::OCDPoint(Vec2 _vec2)
	{
		pPoint = _vec2;
		nxt = nullptr;
		prv = nullptr;
	}
	void OCDPoint::InsertNxt(OCDPoint* _OCDPoint)
	{
		_OCDPoint->prv = this;
		_OCDPoint->nxt = nxt;
		nxt->prv = _OCDPoint;
		nxt = _OCDPoint;
	}
	void OCDPoint::InsertPrv(OCDPoint* _OCDPoint)
	{
		_OCDPoint->nxt = this;
		_OCDPoint->prv = prv;
		prv->nxt = _OCDPoint;
		prv = _OCDPoint;
	}
	void OCDPoint::InsertNxt(Vec2 _vec2)
	{
		OCDPoint* _OCDPoint = new OCDPoint(_vec2);
		InsertNxt(_OCDPoint);
	}
	void OCDPoint::InsertPrv(Vec2 _vec2)
	{
		OCDPoint* _OCDPoint = new OCDPoint(_vec2);
		InsertPrv(_OCDPoint);
	}
	void OCDPoint::DeleteSelf()
	{
		prv->nxt = nxt;
		nxt->prv = prv;
		delete this; //do I need delete this on CEvent Manager?
	}