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
			//������ ���� ĳ���θ� ������ �ʰ� �ϱ� ���ؼ� tem(�߷¿����� �����ʰ� �����̴� ����)������ ������Ʈ ���������� �Ѵ�
			if (m_pTargetObj->GetGravity()->IsGetGravity())
			{
				m_vLookAt = m_pTargetObj->GetJumPos();
			}
			else
			{
				m_vLookAt = m_pTargetObj->GetPos();
			}

			//������ ������ ��� �̹����� �Ѿ��ٸ� ����� �Ѿ ������ x, y��ǥ�� �� �׷� �Ѿư����� �ʰ� �ش� ��ǥ�� �����ؾ���
			//��� x������ �Ѿ���

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
	
	CalDiff();//�Ÿ� �� ���ϱ�
	CheckRangeMap();//���� �Ÿ� ���� �������� �� �������θ� �����̰� �ϱ�
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
	fRatio = m_tEffet.m_fCurTime / m_tEffet.m_fDuration;//�������
	
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
	bf.SourceConstantAlpha = Alpha; //�Ʊ� ���� ���� ���� �ֱ�

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
	//�ϴ� ����
	//1. ���� ���� ������ �����Ӱ� ȭ���� ��� ���� �Ÿ���ŭ�� ���̸� ���� 

	m_fAccTime += fDT;

	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPreLookAt;//���� ���
		if (!vLookDir.IsZero())
		{
			m_vCurLookAt = m_vPreLookAt + vLookDir.NormalRize() * m_fSpeed * fDT;//���� �������� �������� �����ϰ���
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

	//��StartRenderPos.x�� y������ ī�޶� �ٶ󺸴� ũ�⺸�� �۾����� 
	//ī�޶� Ÿ�� ������ ����
	Vec2 vCamLook = m_vCurLookAt;//���� �ٶ󺸰��ִ� ���� renderPos�� �����;��ϳ�
	Vec2 vResoltion = CCore::GetInst()->GetResolution();

	Vec2 vBackGroundCenter = Vec2(m_pBackGround->Width() / 2.f, m_pBackGround->Height() / 2.f);//��� �̹����� ��� ��ġ
	Vec2 vPLayerPos = m_pTargetObj->GetPos();

	//�������̸� ī�޶� tempos�� ���� ������ vPlayerPos�������� �شٸ� ī�޶�� tempos�� ���µ� render�� playerpos(���� ��ġ)�� �������� �ϱ� ������ ������ ����
	//������ �߷��� �ް��ִ� �÷��̾��� playerpos�� tempos�������� �ٲ�����Ѵ�
	if (m_pTargetObj->GetGravity()->IsGetGravity())
	{
		vPLayerPos = m_pTargetObj->GetJumPos();
	}


	//�� ĳ���ͷκ��� ������ x������ ��Ʈ�� ũ�� x��ǥ �ȿ� �־����
	bool isXPass = (vBackGroundCenter.x - m_pBackGround->Width() / 2.f) >= vPLayerPos.x - vResoltion.x / 2.f ||
		(vBackGroundCenter.x + m_pBackGround->Width() / 2.f) <= vPLayerPos.x + vResoltion.x / 2.f;

	//�� ������ y������ ��Ʈ�� ũ�� y��ǥ �ȿ� �־����
	bool isYPass = (vBackGroundCenter.y - m_pBackGround->Height() / 2.f) >= vPLayerPos.y - vResoltion.y / 2.f ||
		(vBackGroundCenter.y + m_pBackGround->Height() / 2.f) <= vPLayerPos.y + vResoltion.y / 2.f;

	if (isXPass)//�Ѿ��ٸ�
	{
		//��ģ �� (����)
		float fLen = abs(vBackGroundCenter.x - vPLayerPos.x); //�� ������Ʈ �Ÿ� 
		float fValue = (vResoltion.x / 2.f + m_pBackGround->Width() / 2.f) - fLen; //�� ��ü�� ũ��/2�� �� - �� ������Ʈ �Ÿ� = ��ģ��

		Vec2 vNorDiff = (vBackGroundCenter - vPLayerPos).NormalRize();
		float fAddValue = vResoltion.x - fValue;

		int iDir = 0;
		if (vNorDiff.x > 0.f)
			iDir = 1;
		else
			iDir = -1;

		SetIsPassX(true);
		//���� ����ŭ ������ �о��ֱ�
		SetEndRangeX(vPLayerPos.x + fAddValue * iDir);
	}
	else
		SetIsPassX(false);


	if (isYPass)//�Ѿ��ٸ�
	{
		//��ģ �� (����)
		float fLen = abs(vBackGroundCenter.y - vPLayerPos.y); //�� ������Ʈ �Ÿ� 
		float fValue = (vResoltion.y / 2.f + m_pBackGround->Height() / 2.f) - fLen; //�� ��ü�� ũ��/2�� �� - �� ������Ʈ �Ÿ� = ��ģ��

		Vec2 vNorDiff = (vBackGroundCenter - vPLayerPos).NormalRize();//y���� Nor.y�� 0.1~0.2�ۿ� �� ���ͼ� ���ص� �̹��� ����
		float fAddValue = vResoltion.y - fValue;

		int iDir = 0;
		if (vNorDiff.y > 0.f)
			iDir = 1;
		else
			iDir = -1;

		SetIsPassY(true);
		//���� ����ŭ ������ �о��ֱ�
		SetEndRangeY(vPLayerPos.y + fAddValue * iDir);
	}
	else
		SetIsPassY(false);
}


