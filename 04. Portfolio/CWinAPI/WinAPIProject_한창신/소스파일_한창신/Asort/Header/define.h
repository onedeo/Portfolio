#pragma once

#define PI 3.141592653

#define SINGLE(type)\
					 public:\
					 static type* GetInst(){static type core; return &core; }\
					private:\
					type();\
					~type();

#define fDT CTimeMgr::GetInst()->GetfDT()
//#define dDT CTimeMgr::GetInst()->GetdDT()

#define KEY_CHECK(key, state)	CKeyMgr::GetInst()->GetKeyState(key)==state

#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

//씬 안에 그룹을 나누는 것 (DEFAULT, PLAYER, BULLETS... 등)
enum class GROUP_TYPE
{	//Render order
	UI,
	OCDPOLYGON,
	DEFAULT,
	PLAYER_PROJECTILE,
	MONSTER_PROJECTILE,
	PLAYER_DEBUFF,
	MONSTER_SUB,
	POKEMON,
	MONSTER,
	PLAYER,

	END
};

enum class SCENE_TYPE
{
	OPENING,
	START,
	CLOSING,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	YELLOW,
	BLUE,
	GREEN,
	BLACK,
	END
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	BLACK,
	WHITE,
	YELLOW,
	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	END
};

enum class DIRECTION
{
	UP, DOWN, RIGHT, LEFT
	,END
};

enum class POKEMON
{
	BULBASAUR,

	END = 5
};