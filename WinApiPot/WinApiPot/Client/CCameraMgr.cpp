#include "pch.h"
#include "CCameraMgr.h"

#include "CCore.h"
#include "CObject.h"
#include "CKeyMgr.h"

#include "CTexture.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CGravity.h"

CCameraMgr::CCameraMgr() :
	m_fAccTime(1.f),
	m_fTime(1.f),
	m_fSpeed(0.f),
	m_bIsPassX(false),
	m_bIsPassY(false),
	m_pTargetObj(nullptr),
	m_pVeilTex(nullptr)
{

}

CCameraMgr::~CCameraMgr()
{

}


void CCameraMgr::update()
{

	if (m_pTargetObj)
	{
		
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			//점프를 했을 캐리턱를 따라가지 않게 하기 위해서 tem(중력영향을 받지않고 움직이는 변수)변수를 오브젝트 포지션으로 한다
			if (m_pTargetObj->GetGravity()->IsGetGravity())
			{
				m_vLookAt = m_pTargetObj->GetJumPos();
			}
			else
			{
				m_vLookAt = m_pTargetObj->GetPos();
			}

			//씬에서 지정한 배경 이미지를 넘었다면 여기로 넘어간 지점의 x, y좌표를 줌 그럼 넘아가지지 않게 해당 좌표를 고정해야함
			//배경 x지점을 넘었나

			if (m_bIsPassY)
			{
				m_vLookAt = Vec2(m_vLookAt.x, m_fEndRangeY);
			}

			if (m_bIsPassX)
			{
				m_vLookAt = Vec2(m_fEndRangeX, m_vLookAt.y);
			}
		}
	}
	else
	{
		if (KEY_HOLD(KEY::DOWN))
		{
			m_vLookAt += Vec2(0.f, 500.f) * fDT;
		}

		if (KEY_HOLD(KEY::UP))
		{
			m_vLookAt -= Vec2(0.f, 500.f) * fDT;
		}

		if (KEY_HOLD(KEY::LEFT))
		{
			m_vLookAt -= Vec2(500.f, 0.f) * fDT;
		}

		if (KEY_HOLD(KEY::RIGHT))
		{
			m_vLookAt += Vec2(500.f, 0.f) * fDT;
		}
	}
	
	CalDiff();//거리 값 구하기
	CheckRangeMap();//구한 거리 값을 바탕으로 맵 안쪽으로만 움직이게 하기
}

void CCameraMgr::init()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreatTexture(L"Veil", (UINT)vResolution.x, (UINT)vResolution.y);
}

void CCameraMgr::render(HDC _dc)
{
	if (m_listCameEffect.empty())
		return;

	tCamEffect& m_tEffet = m_listCameEffect.front();

	m_tEffet.m_fCurTime += fDT;

	float fRatio = 0.f;
	fRatio = m_tEffet.m_fCurTime / m_tEffet.m_fDuration;//진행비율
	
	if (fRatio < 0.f)
		fRatio = 0.f;
	if (fRatio > 1.f)
		fRatio = 1.f;

	int Alpha = 0;

	if (m_tEffet.eEffect == CAM_EFFECT::FADE_OUT)
	{
		Alpha = (int)(255.f * fRatio);
	}

	else if (m_tEffet.eEffect == CAM_EFFECT::FADE_IN)
	{
		Alpha = (int)(255.f * (1.f - fRatio));
	}

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.AlphaFormat = 0;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = Alpha; //아까 만든 진행 비율 넣기

	AlphaBlend(_dc,
		0,0,
		(int)(m_pVeilTex->Width()), (int)(m_pVeilTex->Height()),
		m_pVeilTex->GetDC(),
		0, 0,
		(int)(m_pVeilTex->Width()), (int)(m_pVeilTex->Height()),
		bf);

	if (m_tEffet.m_fCurTime > m_tEffet.m_fDuration)
	{
		m_listCameEffect.pop_front();
	}
}

void CCameraMgr::CalDiff()
{
	//일단 먼저
	//1. 내가 보는 지점에 움직임과 화면의 가운데 값의 거리만큼의 길이를 구함 

	m_fAccTime += fDT;

	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPreLookAt;//방향 잡기
		if (!vLookDir.IsZero())
		{
			m_vCurLookAt = m_vPreLookAt + vLookDir.NormalRize() * m_fSpeed * fDT;//이전 프레임의 지점부터 움직일것임
		}
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_vDiff =  m_vCurLookAt - vResolution / 2.f;

	m_vPreLookAt = m_vCurLookAt;
}

void CCameraMgr::CheckRangeMap()
{
	if (m_pTargetObj == nullptr)
		return;
	CTexture* m_pBackGround = SceneMgr::GetInst()->GetCurSCene()->GetBackGround();

	//요StartRenderPos.x와 y범위가 카메라가 바라보는 크기보다 작아지면 
	//카메라 타겟 범위를 범춤
	Vec2 vCamLook = m_vCurLookAt;//내가 바라보고있는 벡터 renderPos를 가져와야하나
	Vec2 vResoltion = CCore::GetInst()->GetResolution();

	Vec2 vBackGroundCenter = Vec2(m_pBackGround->Width() / 2.f, m_pBackGround->Height() / 2.f);//배경 이미지의 가운데 위치
	Vec2 vPLayerPos = m_pTargetObj->GetPos();

	//점프중이면 카메라가 tempos에 맞춤 때문에 vPlayerPos기준으로 준다면 카메라는 tempos를 보는데 render은 playerpos(점프 위치)를 기준으로 하기 떄문에 오차가 생김
	//떄문에 중력을 받고있는 플레이어라면 playerpos를 tempos기준으로 바꿔줘야한다
	if (m_pTargetObj->GetGravity()->IsGetGravity())
	{
		vPLayerPos = m_pTargetObj->GetJumPos();
	}


	//내 캐릭터로부터 윈도우 x범위가 비트맵 크기 x좌표 안에 있어야함
	bool isXPass = (vBackGroundCenter.x - m_pBackGround->Width() / 2.f) >= vPLayerPos.x - vResoltion.x / 2.f ||
		(vBackGroundCenter.x + m_pBackGround->Width() / 2.f) <= vPLayerPos.x + vResoltion.x / 2.f;

	//내 윈도우 y범위가 비트맵 크기 y좌표 안에 있어야함
	bool isYPass = (vBackGroundCenter.y - m_pBackGround->Height() / 2.f) >= vPLayerPos.y - vResoltion.y / 2.f ||
		(vBackGroundCenter.y + m_pBackGround->Height() / 2.f) <= vPLayerPos.y + vResoltion.y / 2.f;

	if (isXPass)//넘었다면
	{
		//겹친 양 (음수)
		float fLen = abs(vBackGroundCenter.x - vPLayerPos.x); //두 오브젝트 거리 
		float fValue = (vResoltion.x / 2.f + m_pBackGround->Width() / 2.f) - fLen; //두 물체의 크기/2의 합 - 두 오브젝트 거리 = 겹친양

		Vec2 vNorDiff = (vBackGroundCenter - vPLayerPos).NormalRize();
		float fAddValue = vResoltion.x - fValue;

		int iDir = 0;
		if (vNorDiff.x > 0.f)
			iDir = 1;
		else
			iDir = -1;

		SetIsPassX(true);
		//넘은 값만큼 옆으로 밀어주기
		SetEndRangeX(vPLayerPos.x + fAddValue * iDir);
	}
	else
		SetIsPassX(false);


	if (isYPass)//넘었다면
	{
		//겹친 양 (음수)
		float fLen = abs(vBackGroundCenter.y - vPLayerPos.y); //두 오브젝트 거리 
		float fValue = (vResoltion.y / 2.f + m_pBackGround->Height() / 2.f) - fLen; //두 물체의 크기/2의 합 - 두 오브젝트 거리 = 겹친양

		Vec2 vNorDiff = (vBackGroundCenter - vPLayerPos).NormalRize();//y축은 Nor.y가 0.1~0.2밖에 안 나와서 곱해도 미미한 양임
		float fAddValue = vResoltion.y - fValue;

		int iDir = 0;
		if (vNorDiff.y > 0.f)
			iDir = 1;
		else
			iDir = -1;

		SetIsPassY(true);
		//넘은 값만큼 옆으로 밀어주기
		SetEndRangeY(vPLayerPos.y + fAddValue * iDir);
	}
	else
		SetIsPassY(false);
}


