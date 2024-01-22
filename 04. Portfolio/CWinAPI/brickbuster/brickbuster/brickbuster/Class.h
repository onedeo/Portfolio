#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include <string>
#include <tchar.h>

#define default_gap_x 30
#define default_gap_y 80

static RECT rectView = { 0,0,654,541 };
enum { green, yellow, orange, red };

class Bricks
{
private:
	int color;
	int width;
	int height;
	int gap_x;
	int gap_y;
	int location;
	bool alive;
	POINT p[4];

public:
	Bricks();
	void Hit();
	void set_Color(int color);
	void set_Location(int number);
	void Draw(HDC hdc);
	void Update();
	void re_Spawn();

	friend void Ball_Hit();
};

class Paddle
{
private:
	int width;
	int height;
	int speed;
	POINT p[4];

public:
	Paddle();
	void Move_Right(int direction);
	void Hit();
	void Draw(HDC hdc);
	void Update();
	void to_Center();
	POINT* get_Points();

	friend void Ball_Hit();
};

class Ball
{
private:
	int radius;
	int life;
	int speed;
	bool start;
	POINT center;
	POINT vector;
	RECT area;

public:
	Ball();
	void Start(int start);
	void Draw(HDC hdc);
	void Update(POINT* padp);
	void Dead();
	int Gameover();
	void set_Area(RECT area);
	bool get_Start() { return start; }
	int get_Life();
	void set_Life(int life);
	
	friend void Ball_Hit();
};

class UI
{
private:
	RECT area;

public:
	//UI();
	void set_Area(RECT area);

	void Draw_Top(HDC hdc, int point, TCHAR* name);
	void Draw_PressStart(HDC hdc);
	void Draw_TypeName(HDC hdc, TCHAR* name);
	void Draw_Area(HDC hdc);
	void Draw_Bottom(HDC hdc, int life);
	void Draw_GameOver(HDC hdc);
};

