#pragma once
struct Vec2;
struct Point;

struct Point
{
	int x, y;
public:
	Point();
	Point(Vec2 _vec2);
	Point(float _x, float _y);
public:
	bool operator==(const Point& _ivec2);
	bool operator==(Vec2& _vec2);
	bool operator==(Point& _p);

	bool AroundEqual(Point p);

	void operator=(Vec2& _vec2);
	Point& operator+(Point& _p);
	Point& operator+(Vec2 _vec2);

public:
	Vec2 ToVec2();
};

struct Vec2
{
	float x;
	float y;

public:
	float Length();
	Vec2& Normalize();
	const Point ToPoint();
public:
	void operator = (Point _pt);
	Vec2& operator +(Vec2 _vec2);
	Vec2& operator +(Point _vec2);
	Vec2& operator* (float a);
	bool operator==(const Vec2& _vec2);
	bool operator==(const Point& _ivec2);
	void operator=(const Point& _ivec2);


public:
	Vec2();
	Vec2(float _x, float _y);
	Vec2(int _x, int _y);
	Vec2(LONG _x, LONG _y);

	Vec2(const Point& _pt);
	//Vec2(const POINT& _pt);
	Vec2(float _xy);
	Vec2(int _xy);
};

struct OCDPoint
{
	Point pPoint;
	OCDPoint* nxt;
	OCDPoint* prv;

public:
	OCDPoint();
	OCDPoint(Vec2 _vec2);
	void InsertNxt(OCDPoint* _OCDPoint);
	void InsertPrv(OCDPoint* _OCDPoint);
	void InsertNxt(Vec2 _vec2);
	void InsertPrv(Vec2 _vec2);
	void DeleteSelf();
};

struct PackOCG
{
	Point* ocgPoint;
	int ocgCnt;
	DIRECTION dirStart;
	bool bClockwise;
	bool bSameDir;

public:
	PackOCG()
	{
		ocgPoint = nullptr;
		ocgCnt = 0;
		dirStart = DIRECTION::END;
		bClockwise = false;
		bSameDir = false;
	}
	PackOCG(Point* _point, int _cnt, bool _clockwise, DIRECTION _dir, bool _samedir)
	{
		ocgPoint = _point;
		ocgCnt = _cnt;
		dirStart = _dir;
		bClockwise = _clockwise;
		bSameDir = _samedir;
	}
};