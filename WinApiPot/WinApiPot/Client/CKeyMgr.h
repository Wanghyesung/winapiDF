#pragma once

enum class KEY_STATE
{
	TAP,//���� ������ ��
	HOLD,//���� �����ӿ��� ������ ���ݵ� ������ ��
	AWAY,//�� �����ӿ��� ������ ������ ���� ��
	DOUBLE,//������ �ð��ȿ� push�� true�� key�� �ٽ� ������ ��
	NONE,//�ƹ��͵� ������ ���� ��
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, Z, X, C, V, B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,

	LAST = 32,
};


struct KeyInfo
{
	KEY_STATE eState;
	bool	  bPrevPush;
};


class CKeyMgr
{
	SINGLE(CKeyMgr)

private:
	vector<KeyInfo> m_vecKey;//���� �ȿ� Ű ���°����� �ֱ�
	Vec2			m_vCurMousePos;
	

public:
	void init();
	void update();


	Vec2	  GetMousePos() {return m_vCurMousePos;}
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }


};

