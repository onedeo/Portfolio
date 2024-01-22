#include "Class.h"

Bricks::Bricks()
{
	width = 50;
	height = 20;
	gap_x = 10;
	gap_y = 4;
}

void Bricks::Hit()
{
	color--;
	//ADD: hit animation input
	if (color < 0) alive = false;
}

void Bricks::set_Color(int color)
{
	this->color = color;
}

void Bricks::set_Location(int number)
{
	this->location = number;
}

void Bricks::Draw(HDC hdc)
{
		//set brush
	if (alive == 0) return;

	int red, green, blue;
	switch (this->color)
	{
		case 0: //ÃÊ·Ï
			red = 0;
			green = 255;
			blue = 0;
			break;
		case 1: //³ë¶û
			red = 255;
			green = 255;
			blue = 0;
			break;
		case 2: //ÁÖÈ²
			red = 255;
			green = 165;
			blue = 0;
			break;
		case 3: //»¡°­
			red = 255;
			green = 0;
			blue = 0;
			break;
		default:
			red = 0;
			green = 0;
			blue = 0;
			break;
	}

	HBRUSH hBrush = CreateSolidBrush(RGB(red, green, blue));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		//draw brick
	p[0].x = (gap_x + width) * (location % 10)+ default_gap_x;
	p[0].y = (gap_y + height) * (location / 10) + default_gap_y;
	p[1] = { p[0].x + width, p[0].y };
	p[2] = { p[0].x + width, p[0].y + height };
	p[3] = { p[0].x, p[0].y + height };

	Polygon(hdc, p, 4);
	DeleteObject(hBrush);
}

void Bricks::re_Spawn()
{
	this->alive = 1;
}

POINT* Paddle::get_Points()
{
	return p;
}

Paddle::Paddle()
{
	//default width=100
	width = 100;
	height = 10;
	speed = 2;
	to_Center();
}

void Paddle::Move_Right(int direction)
{
	bool can_Left = (p[0].x > default_gap_x);
	bool can_Right = (p[1].x < rectView.right - default_gap_x);
	bool Go = false;
	if (direction < 0 && can_Left) Go = true;
	else if (direction > 0 && can_Right) Go = true;
	if (Go)
	{
		for (int i = 0; i < 4; i++)
		{
			p[i].x += speed * direction;
		}
	}
}

void Paddle::Hit()
{
	//if()
}

void Paddle::Draw(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(128, 128, 128));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Polygon(hdc, p, 4);
	DeleteObject(hBrush);
}

void Paddle::Update()
{
}

void Paddle::to_Center()
{
	p[0].x = p[3].x = rectView.right / 2 - width / 2;
	p[1].x = p[2].x = p[0].x + width;
	p[2].y = p[3].y = rectView.bottom - default_gap_y;
	p[0].y = p[1].y = p[2].y - height;
}

Ball::Ball()
{
	radius = 7;
	life = 2;
	speed = 1;
	start = 0;
	vector = { 1,-1 };
}

void Ball::Start(int start)
{
	this->start = start;
	vector.y = abs(vector.y) * -1;
}

void Ball::Draw(HDC hdc)
{
	Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
}

void Ball::Update(POINT* padp)
{
	if (start == 0)
	{
		center.x = padp[0].x + (padp[1].x - padp[0].x) / 2;
		center.y = padp[0].y - radius;
	}
	else
	{
		if (center.y - radius<area.top + 1)
		{
			vector.y *= -1;
		}
		if (center.x + radius > area.right - 1 || center.x - radius < area.left + 1)
		{
			vector.x *= -1;
		}
		center.x += vector.x*speed;
		center.y += vector.y*speed;
	}
	if (center.y + radius == area.bottom)
	{
		Dead();
	}
}

void Ball::Dead()
{
	start = 0;
	life--;
	vector.y = abs(vector.y) * -1;
}

int Ball::Gameover()
{
	if (life < 0)
		return 1;
	return 0;
}

void Ball::set_Area(RECT area)
{
	this->area = area;
}

int Ball::get_Life()
{
	return life;
}

void Ball::set_Life(int life)
{
	this->life = life;
}

void UI::set_Area(RECT area)
{
	this->area = area;
}

void UI::Draw_Top(HDC hdc, int point, TCHAR* name)
{
	TextOut(hdc, area.left, area.top - 20, name, _tcslen(name));

	TCHAR print[100];
	_stprintf(print, _T("POINT  %d00"), point);

	TextOut(hdc, area.right - 150, area.top - 20, print, _tcslen(print));
}

void UI::Draw_PressStart(HDC hdc)
{
	TCHAR str[] = _T("PRESS SPACE TO CONTINUE");
	TextOut(hdc, area.right / 2-90, area.bottom * 2 / 3+30, str, _tcslen(str));
}

void UI::Draw_TypeName(HDC hdc, TCHAR* name)
{
	TCHAR str[] = _T("ENTER YOUR NAME");
	TextOut(hdc, area.right / 2 - 90, area.bottom * 2 / 3 -40, str, _tcslen(str));
	TextOut(hdc, area.right / 2 - 90, area.bottom * 2 / 3-10, name, 9);
}

void UI::Draw_Area(HDC hdc)
{
	Rectangle(hdc, rectView.left + default_gap_x - 10, rectView.top + 40,
			  rectView.right - default_gap_x + 10, rectView.bottom - 30);
}

void UI::Draw_Bottom(HDC hdc, int life)
{
	RECT circle = { rectView.left + 30, rectView.bottom - 25, rectView.left + 50, rectView.bottom - 5 };
	int gap = 35;
	
	for (int i = 0; i < life; i++)
	{
		Ellipse(hdc, circle.left+i*gap, circle.top, circle.right + i * gap, circle.bottom);
	}


}

void UI::Draw_GameOver(HDC hdc)
{
	TCHAR str[] = _T("THANK YOU FOR PLAYING.");
	TextOut(hdc, area.right / 2 - 90, area.bottom * 2 / 3 - 40, str, _tcslen(str));

	TCHAR str1[] = _T("DO YOU WANT PLAY AGAIN?");
	TextOut(hdc, area.right / 2 - 90, area.bottom * 2 / 3 - 20, str1, _tcslen(str1));

	TCHAR str2[] = _T("1. YES            2. NO");
	TextOut(hdc, area.right / 2 - 90, area.bottom * 2 / 3, str2, _tcslen(str2));
}
