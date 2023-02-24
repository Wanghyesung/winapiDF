#include "pch.h"

#include "CAnimator.h"

#include "CAnimation.h"
#include "CKeyMgr.h"
#include "CSkillState.h"

CAnimator::CAnimator() :

	m_pOwner(nullptr),
	m_pCurAnim(nullptr),
	m_pOtherAnim(nullptr),
	m_bRepeat(false),
	r(255),g(255),b(255)
{
}
CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLt, Vec2 _vSliceSzie, Vec2 _vStep, Vec2 _vOffset, float _fDuration, UINT _iframeCount)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(nullptr == pAnim);//�̹� �ִϸ��̼��� �����ϸ� assert

	//�ƴѰ�쿡 ���ο� �ִϸ��̼�
	pAnim = new CAnimation;

	pAnim->SetName(_strName);//�̸� �Ҵ� ������ �̸��� animator��� ����
	pAnim->m_pAnimator = this; //�� �ִϸ����Ϳ� ����
	pAnim->Create(_pTex, _vLt, _vSliceSzie, _vStep, _vOffset, _fDuration,_iframeCount);


	m_mapAnim.insert(make_pair(_strName, pAnim));//���ϸ��̼� map�� ����
}

void CAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	CAnimation* pAnim = new CAnimation;
	pAnim->Load(_strRelativePath);

	pAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;//�������
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat, CSkillState* _pCurSkill)
{
	m_pCurAnim = FindAnimation(_strName);
	//�� ���� ��ų�� ������ ���� ����
	_pCurSkill->SetCurFram(m_pCurAnim->GetCurFrame());
	m_bRepeat = _bRepeat;//�������
}


void CAnimator::PlayMulti(const wstring& _strMainName, const wstring& _strOtherName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strMainName);
	m_pOtherAnim = FindAnimation(_strOtherName);
	m_pOtherAnim->SetFram(m_pCurAnim->GetCurFrame(),false);//�ٸ� �ִϸ��̼ǵ� ������ �Ȱ���
	m_bRepeat = _bRepeat;//�������
}




CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);
	
	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CAnimator::SetRBG(int _r, int _g, int _b)
{
	r = _r;
	g = _g;
	b = _b;
}

void CAnimator::finalupdate()
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->update();
		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFram(0);
		}
	}
}

void CAnimator::render(HDC _dc)
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->render(_dc);
	}	
}
