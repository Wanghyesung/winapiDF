#pragma once

enum class KEY_STATE
{
	TAP,//지금 눌렀을 때
	HOLD,//이전 프레임에도 누르고 지금도 눌렀을 떄
	AWAY,//전 프레임에는 눌렀고 지금은 땠을 때
	DOUBLE,//정해진 시간안에 push가 true인 key가 다시 눌렸을 때
	NONE,//아무것도 누르지 않을 떄
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
	vector<KeyInfo> m_vecKey;//벡터 안에 키 상태값들을 넣기
	Vec2			m_vCurMousePos;
	

public:
	void init();
	void update();


	Vec2	  GetMousePos() {return m_vCurMousePos;}
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }


};

