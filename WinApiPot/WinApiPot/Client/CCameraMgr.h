#pragma once

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE
};

struct tCamEffect
{
	CAM_EFFECT eEffect;
	float		m_fCurTime;
	float		m_fDuration;
};


class CObject;
class CTexture;

class CCameraMgr
{
	SINGLE(CCameraMgr)

public:
	void update();
	void init();
	void render(HDC _dc);

private:
	Vec2	m_vLookAt;//���� �ٶ󺸴� ����
	Vec2	m_vCurLookAt;//���� (�������� ���� ��Ȳ)���� ���� 
	Vec2	m_vPreLookAt;//���� ����
	CObject* m_pTargetObj;

	Vec2   m_vDiff; //������Ʈ������ ����

	float	m_fTime; //Ÿ���� ���󰡴� �ð�
	float	m_fSpeed;//Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float   m_fAccTime;//���� �ð�


	CTexture* m_pVeilTex;
	list< tCamEffect> m_listCameEffect;
	//bool m_bAttive;//ī�޶��� ������ �޳�

	//���� x, y��ǥ�� �Ѱ峪
	bool m_bIsPassX;
	bool m_bIsPassY;

	//���� ���� �ʴ� �ִ� x y ����
	float m_fEndRangeX;
	float m_fEndRangeY;

public:
	void SetTarget(Vec2 _v) { m_vLookAt = _v; }
	void SetTargetObj(CObject* _pObj) { m_pTargetObj = _pObj; }
	CObject* GetTargetObj() { return m_pTargetObj; }


	Vec2 GetLookAt() { return m_vCurLookAt; }

	void SetLookAt(Vec2 _vLook)
	{
		m_vLookAt = _vLook;
		m_fSpeed = ((m_vLookAt - m_vPreLookAt).Length() / m_fTime);
		m_fAccTime = 0;
	}

public:
	void SetIsPassX(bool _b) { m_bIsPassX = _b; }
	void SetIsPassY(bool _b) { m_bIsPassY = _b; }

	void SetEndRangeX(float _fX)
	{
		m_fEndRangeX = _fX;
	}

	void SetEndRangeY(float _fY)
	{
		m_fEndRangeY = _fY;
	}

public:
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }


	void FadeIn(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.m_fDuration = _fDuration;
		ef.m_fCurTime = 0.f;
		m_listCameEffect.push_back(ef);

		if (0.f == _fDuration)
			assert(nullptr);
	}

	void FadeOut(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.m_fDuration = _fDuration;
		ef.m_fCurTime = 0.f;
		m_listCameEffect.push_back(ef);

		if (0.f == _fDuration)
			assert(nullptr);
	}

private:
	void CalDiff();//���� ������ ��� ��ü�� �־��� ���� �����

	void CheckRangeMap();
};

