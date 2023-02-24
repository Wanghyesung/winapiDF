#include "pch.h"
#include "CAnimation.h"

#include "CAnimator.h"
#include "CObject.h"
#include "CTexture.h"
#include "CTimeMgr.h"

#include "CPlayer.h"

#include "CPathMgr.h"

#include "CResMgr.h"

#include "CCameraMgr.h"

#include "CSkillMgr.h"

CAnimation::CAnimation() :
	m_pTex(nullptr),
	m_pAnimator(nullptr),
	m_bFinish(false),
	m_fAccTime(0.f),
	m_iCurFrm(0)
{
}

CAnimation::~CAnimation()
{
	
}



void CAnimation::update()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT;

	
	if (m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{
		++m_iCurFrm;
		if (m_iCurFrm >= m_vecFrm.size())
		{
			m_bFinish = true;
			m_iCurFrm = -1;
			m_fAccTime = 0.f;
			return;
		}
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;//dT���� Ƣ� fDuration���� �� ũ�� �Ѿ �� ���� ���� ������ �ִϸ��̼� ���� ��������
	}
	
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;

	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();

	vPos += m_vecFrm[m_iCurFrm].vOffset;

	vPos = CCameraMgr::GetInst()->GetRenderPos(vPos);

	//�»��, ���ϴ�, �»�����κ����� �ϴܰ�
	TransparentBlt(_dc,
		(int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f),
		(int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f),
		(int)(m_vecFrm[m_iCurFrm].vSlice.x),
		(int)(m_vecFrm[m_iCurFrm].vSlice.y),
		m_pTex->GetDC(),
		(int)(m_vecFrm[m_iCurFrm].vLt.x),
		(int)(m_vecFrm[m_iCurFrm].vLt.y),
		(int)(m_vecFrm[m_iCurFrm].vSlice.x),
		(int)(m_vecFrm[m_iCurFrm].vSlice.y),
		RGB(m_pAnimator->r, m_pAnimator->g, m_pAnimator->b));
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLt, Vec2 _vSliceSzie, Vec2 _vStep, Vec2 _vOffset, float _fDuration, UINT _iframeCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};

	for (UINT i = 0; i < _iframeCount; ++i)
	{
		frm.vLt = _vLt + _vStep * (float)i;
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSzie;
		frm.vOffset = _vOffset;
		m_vecFrm.push_back(frm);
	}
}


void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath =  CPathMgr::GetInst()->GetContenPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	assert(pFile);


	fprintf(pFile, "[Animation Name\n");
	string name = string(m_strName.begin(), m_strName.end());//string���� �������� ����� ������ �� �ְ� ���̳ʸ����� �ƴ϶� ���ڿ��� �����
	fprintf(pFile, name.c_str());
	fprintf(pFile, "\n");
	
	//���� �� �ؽ��� �̸�
	fprintf(pFile, "[Texture Name]\n");
	string TexName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	fprintf(pFile, TexName.c_str());
	fprintf(pFile, "\n");

	//���
	fprintf(pFile, "[Path Name]\n");
	string pathName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
	fprintf(pFile , pathName.c_str());
	fprintf(pFile, "\n");

	//������ ��
	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d\n", (int)m_vecFrm.size());


	for (int i = 0; i < m_vecFrm.size(); ++i)
	{
		fprintf(pFile, "[Frame Index]\n");
		fprintf(pFile, "%d\n", (int)i);

		fprintf(pFile, "[LEFT Top]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vLt.x, (int)m_vecFrm[i].vLt.y);

		fprintf(pFile, "[Slice Size]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vSlice.x, (int)m_vecFrm[i].vSlice.y);

		fprintf(pFile, "[Offset]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vOffset.x, (int)m_vecFrm[i].vOffset.y);

		fprintf(pFile, "[Duration]\n");
		fprintf(pFile, "%f\n", m_vecFrm[i].fDuration);

		fprintf(pFile, "\n\n");
	}

	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContenPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	assert(pFile);

	string str;
	char szBuffer[256] = {};

	FScanf(szBuffer, pFile);
	FScanf(szBuffer, pFile); //�� ���ڸ� �����Ƿμ� �ڿ� Name�� �ȵ��� �ִϸ��̼��� �̸������� �� ����
	str = szBuffer;
	m_strName = wstring(str.begin(), str.end());

	FScanf(szBuffer, pFile);
	FScanf(szBuffer, pFile);
	str = szBuffer;
	wstring strKey = wstring(str.begin(), str.end());

	FScanf(szBuffer, pFile);
	FScanf(szBuffer, pFile);
	str = szBuffer;
	wstring strRelativePath = wstring(str.begin(), str.end());

	m_pTex = CResMgr::GetInst()->LoadTextur(strKey, strRelativePath);

	//������ count
	int iFramCount = 0;
	FScanf(szBuffer, pFile);
	fscanf_s(pFile, "%d", &iFramCount);

	tAnimFrm frm = {};
	for (size_t i = 0; i < iFramCount; ++i)
	{
		POINT pt = {};
		while (true)
		{
			FScanf(szBuffer, pFile);

			if (!strcmp("[Frame Index]", szBuffer))
			{
				fscanf_s(pFile, "%d", &pt.x);
			}

			else if (!strcmp("[LEFT Top]", szBuffer))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);

				frm.vLt = pt;
			}

			else if (!strcmp("[Slice Size]", szBuffer))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);

				frm.vSlice = pt;
			}

			else if (!strcmp("[Offset]", szBuffer))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);

				frm.vOffset = pt;
			}

			else if (!strcmp("[Duration]", szBuffer))
			{
				fscanf_s(pFile, "%f", &frm.fDuration);
				break; //�̹� ������ �� ����
			}
		}
		m_vecFrm.push_back(frm);
	}

	fclose(pFile);
}

