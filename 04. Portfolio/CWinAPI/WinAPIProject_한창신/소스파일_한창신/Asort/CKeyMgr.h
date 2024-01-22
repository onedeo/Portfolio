
#include "pch.h"
//	1. ������ ����ȭ
//	���������� ������ ���� Ű�� ���� ������ �̺�Ʈ�� ��������

//	2. Ű �Է� �̺�Ʈ ó��
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
	KEY_STATE		eState;	//Ű�� ���� ��
	bool					bPrevPushed;	//���� �����ӿ��� ���ȴ��� ����
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
