
#include "pch.h"
//	1. 프레임 동기화
//	동일프레임 내에서 같은 키에 대해 동일한 이벤트를 가져간다

//	2. 키 입력 이벤트 처리
//tap, hold, away

enum class KEY_STATE
{
	NONE,
	TAP,
	HOLD,
	AWAY
};
enum class KEY
{
	LEFT, RIGHT, UP, DOWN,
	SPACE,
	LSHIFT,
	Q,W,E,R,
	ESC,
	ENTER,
	TAB,

	END
};

struct tKeyInfo
{
	KEY_STATE		eState;	//키의 상태 값
	bool					bPrevPushed;	//이전 프레임에서 눌렸는지 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> vecKey;

public:
	void Init();
	void Update();
	
public:
	KEY_STATE GetKeyState(KEY _eKey)
	{
		return vecKey[(int)_eKey].eState;
	}
};
