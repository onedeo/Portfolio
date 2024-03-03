#pragma once
#include "pch.h"

class CObject;

void CreateObject(CObject* _pObj, GROUP_TYPE _eType);
void myDeleteObject(CObject* _pObj, GROUP_TYPE _eType);

void ChangeScene(SCENE_TYPE _nxt);

float GetDistance(Vec2 p1, Vec2 p2);

bool IsBetweenTwo(int p1, int p2, int target);
bool IsBetweenX(Vec2 v1, Vec2 v2, Vec2 target);
bool IsBetweenY(Vec2 v1, Vec2 v2, Vec2 target);
bool IsBetweenXorY(Vec2 v1, Vec2 v2, Vec2 target);

bool IsBetweenX(Point p1, Point p2, Vec2 target);
bool IsBetweenY(Point p1, Point p2, Vec2 target);
bool IsBetweenXorY(Point p1, Point p2, Vec2 target);

bool IsOnXAxis(Point p1, Point p2, Vec2 target);
bool IsOnYAxis(Point p1, Point p2, Vec2 target);
bool IsOnXorYAxis(Point p1, Point p2, Vec2 target);


int CountLinesOnDirection(Vec2 _pos, OCDPoint* _ocdPoint, DIRECTION _dir);
int CountLinesOnDirection(Point _pCen, OCDPoint* _ocdPoint, DIRECTION _dir);

