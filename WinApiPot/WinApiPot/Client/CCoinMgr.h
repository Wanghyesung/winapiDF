#pragma once
class CTexture;


class CCoinMgr
{
	SINGLE(CCoinMgr);

public:
	void init();
	//���� ȭ�� �׸���
	void render(HDC _dc);
	void update();


	void StartUpdate(Vec2 _vDeadPos);
	void Resurrection();

	const UINT& GetCoinCount() { return m_iCoinCount; }

private:
	//��Ȱ���ɽð�
	float m_fResTime;

	bool m_bIsDead;
	UINT m_iCoinCount;

	//��Ȱ����
	Vec2 m_vResPos;


	//��Ȱī��Ʈ
	vector<CTexture*> m_vecCountTex;
	//���μ�
	vector<CTexture*> m_vecCoinCountTex;
	CTexture* m_pCoinTex;

};

