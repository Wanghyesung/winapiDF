#pragma once

class CTexture;

enum class KEY_STATE
{
	TAP,	//지금 누른 상태 
	HOLD,	//이전 프레임에도 눌렀고 지금도 누른 상태
	AWAY,	//전 프레임에는 눌렀고 지금은 땐 상태
	NONE,	//아무것도 누르지 않은 상태
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	KEY1, KEY2, KEY3, KEY4, KEY5,KEY6,


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

	LAST = 38,
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
	
	vector<CTexture*> m_vecKeyTex;

public:
	void init();
	void update();

	CTexture* GetKeyTex(const wstring& _strKey);

	Vec2	  GetMousePos() {return m_vCurMousePos;}
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState; }


};

