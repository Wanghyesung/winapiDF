#pragma once
class CTexture;


class CCoinMgr
{
	SINGLE(CCoinMgr);

public:
	void init();
	//코인 화면 그리기
	void render(HDC _dc);
	void update();


	void StartUpdate(Vec2 _vDeadPos);
	void Resurrection();

	const UINT& GetCoinCount() { return m_iCoinCount; }

private:
	//부활가능시간
	float m_fResTime;

	bool m_bIsDead;
	UINT m_iCoinCount;

	//부활지점
	Vec2 m_vResPos;


	//부활카운트
	vector<CTexture*> m_vecCountTex;
	//코인수
	vector<CTexture*> m_vecCoinCountTex;
	CTexture* m_pCoinTex;

};

