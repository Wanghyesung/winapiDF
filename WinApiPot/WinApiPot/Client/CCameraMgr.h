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
	Vec2	m_vLookAt;//지금 바라보는 방향
	Vec2	m_vCurLookAt;//현재 (목적지로 가는 상황)보는 방향 
	Vec2	m_vPreLookAt;//이전 방향
	CObject* m_pTargetObj;

	Vec2   m_vDiff; //오브젝트끼리의 차이

	float	m_fTime; //타겟을 따라가는 시간
	float	m_fSpeed;//타겟을 따라가는데 걸리는 시간
	float   m_fAccTime;//누적 시간


	CTexture* m_pVeilTex;
	list< tCamEffect> m_listCameEffect;
	//bool m_bAttive;//카메라의 영향을 받냐

	//맵의 x, y좌표를 넘겼나
	bool m_bIsPassX;
	bool m_bIsPassY;

	//맵을 넘지 않는 최대 x y 범위
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
	void CalDiff();//내가 움진인 양과 물체가 멀어질 양을 계산함

	void CheckRangeMap();
};

