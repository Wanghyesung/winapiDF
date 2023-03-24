#include "pch.h"
#include "CInterFace.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CItem.h"
#include "CObject.h"
#include "CHP.h"
#include "CMP.h"

#include "CSkillMgr.h"
#include "CInventoryMgr.h"
#include "CInventory.h"


CInterFace::CInterFace():
	m_pInterFaceTex(nullptr),
	m_vecItem{},
	m_vecSKillTex{},
	m_vecCoolDownTex{},
	m_vecKeyTex{},
	m_vItemStartPos(Vec2(150.f, 655.f)),
	m_vItemEndPos(Vec2(520.f, 693.f)),
	m_vItemStep(Vec2(62.f, 38.f))

{
	SetName(L"InterFace");
	m_pInterFaceTex = CResMgr::GetInst()->LoadTextur(L"InterFace", L"..\\OutPut\\bin_release\\Content\\Interface\\playerInterface.bmp");
	SetScale(Vec2(1280.f, 100.f));

	m_vecSKillTex.resize(5);
	m_vecCoolDownTex.resize(5);
	m_vecItem.resize(6);
	m_vecKeyTex.resize(12);

	//스킬 이미지
	m_vecSKillTex[0] = CResMgr::GetInst()->LoadTextur(L"Kick", L"..\\OutPut\\bin_release\\Content\\SKill\\Kick.bmp");
	m_vecSKillTex[1] = CResMgr::GetInst()->LoadTextur(L"MachKick", L"..\\OutPut\\bin_release\\Content\\SKill\\MachKick.bmp");
	m_vecSKillTex[2] = CResMgr::GetInst()->LoadTextur(L"Windmill", L"..\\OutPut\\bin_release\\Content\\SKill\\Windmill.bmp");
	m_vecSKillTex[3] = CResMgr::GetInst()->LoadTextur(L"RandFire", L"..\\OutPut\\bin_release\\Content\\SKill\\RandomFire.bmp");
	m_vecSKillTex[4] = CResMgr::GetInst()->LoadTextur(L"WalkFire", L"..\\OutPut\\bin_release\\Content\\SKill\\WalkFire.bmp");

	m_vecCoolDownTex[0] = CResMgr::GetInst()->LoadTextur(L"Kick_", L"..\\OutPut\\bin_release\\Content\\SKill\\Kick_.bmp");
	m_vecCoolDownTex[1] = CResMgr::GetInst()->LoadTextur(L"MachKick_", L"..\\OutPut\\bin_release\\Content\\SKill\\MachKick_.bmp");
	m_vecCoolDownTex[2] = CResMgr::GetInst()->LoadTextur(L"Windmill_", L"..\\OutPut\\bin_release\\Content\\SKill\\Windmill_.bmp");
	m_vecCoolDownTex[3] = CResMgr::GetInst()->LoadTextur(L"RandFire_", L"..\\OutPut\\bin_release\\Content\\SKill\\RandomFire_.bmp");
	m_vecCoolDownTex[4] = CResMgr::GetInst()->LoadTextur(L"WalkFire_", L"..\\OutPut\\bin_release\\Content\\SKill\\WalkFire_.bmp");


	m_vecNumber.resize(9);
	//자식 오브젝트 추가
	for (int i = 0; i < 9; ++i)
	{
		wstring strNum = std::to_wstring(i + 1);
		m_vecNumber[i] = CResMgr::GetInst()->LoadTextur(L"Number" + strNum, L"..\\OutPut\\bin_release\\Content\\Item\\" + strNum + L".bmp");
	}

	//스킬 키랑 아이템1~6번째 텍스쳐 가져오기
	//m_vecKeyTex[0] = CResMgr::GetInst()->LoadTextur()

}

CInterFace::~CInterFace()
{
	int a = 10;
}

void CInterFace::update()
{
	//여기서 포션
	if (KEY_TAP(KEY::KEY1))
	{
		if (m_vecItem[0] != nullptr)
		{
			m_vecItem[0]->UseItem();
		}
	}
	else if (KEY_TAP(KEY::KEY2))
	{

	}

	else if (KEY_TAP(KEY::KEY3))
	{

	}

	else if (KEY_TAP(KEY::KEY4))
	{

	}

	else if (KEY_TAP(KEY::KEY5))
	{

	}

	else if (KEY_TAP(KEY::KEY6))
	{

	}
	CUI::update();

}

void CInterFace::MouseOn()
{

}

void CInterFace::MouseLbtnDown()
{
	
}

void CInterFace::MouseLbtnUp()
{

}

void CInterFace::MouseLbtnClicked()
{

}

void CInterFace::MoveIoInterface(CItem* _pItem)
{
	//아이템을 넣을 해시맵 인덱스
	UINT iItemIndex = 0;
	UINT iFinalIndx = 0;

	Vec2 vOtherDragePrePos = _pItem->m_vDragePrePos;
	Vec2 vOtherItemPos = _pItem->GetPos();

	//일단 아무 값이나
	float fMinLen = 1000.f;
	Vec2  vMinVec = vOtherDragePrePos;

	for (int x = m_vItemStartPos.x; x <= m_vItemEndPos.x; x += m_vItemStep.x)
	{
		if (Vec2(x, 655) == vOtherDragePrePos)
		{
			++iItemIndex;
			continue;
		}
		//내 인벤토리 아이템 위치칸과 아이템 들어올 아이템 위치
		float fLen = abs(abs(vOtherItemPos.x) - abs(x));

		if (fLen <= 55.5f && fMinLen >= fLen)
		{
			//내 아이템을 넣을 인덱스
			iFinalIndx = iItemIndex;
			fMinLen = fLen;
			vMinVec = Vec2(x, 655);
		}
		++iItemIndex;
	}

	//내 원래 위치에 두었다면
	if (vMinVec == vOtherDragePrePos)
	{
		_pItem->m_tItemInfo.m_vPos = vOtherDragePrePos;
		_pItem->SetPos(vOtherDragePrePos);
		return;
	}

	
	//원래 인벤토리에 있던 아이템인지
	if (!_pItem->m_bIsInterfacePos)
	{
		_pItem->m_bIsInterfacePos = true;
		//아이템 크기 키우기
		_pItem->SetItemScale(m_vItemStep);
		//부모 위치 영향 안받게
		_pItem->SetParentAfeccted(false);
		//원래 부모UI 버리고 interfaceUI를 부모로
		_pItem->DeleteChildUI();
		AddChildUI(_pItem);

		//여기서 둘 자리에 아이템이 있는지 검사
		CItem* pItem = getItemThisIndex(iFinalIndx);
		if(pItem != nullptr)
			changeInvenotry(pItem, vOtherDragePrePos);
	}

	//인터페이스 창에서 바꾼거라면
	else
	{
		//해당 인덱스에 있는 아이템 가져오기
		CItem* pItem = getItemThisIndex(iFinalIndx);
		if (pItem != nullptr)
		{
			changeItemIndex(pItem, _pItem);
		}
		else
		{
			int iIndex = GetItemIndex(_pItem);
			m_vecItem[iIndex] = nullptr;
		}
	}

	m_vecItem[iFinalIndx] = _pItem;
	_pItem->m_tItemInfo.m_vPos = vMinVec;
	_pItem->SetPos(vMinVec);

}

void CInterFace::changeInvenotry(CItem* _pItem, Vec2 _vOtherDragePrePos)
{
	int iIndex = GetItemIndex(_pItem);
	//둘 자리에 아이템이 없는상태라면 그냥 return
	if (iIndex == -1)
		return;
	
	CItem* pPreItem = getItemThisIndex(iIndex);

	//인벤토리로 보내기
    pPreItem->m_bIsInterfacePos = false;
	pPreItem->SetItemScale(Vec2(28.f,28.f));
	//부모 위치 영향 안받게
	pPreItem->SetParentAfeccted(true);
	//원래 부모UI 버리고 interfaceUI를 부모로
	pPreItem->DeleteChildUI();
	
	pPreItem->m_tItemInfo.m_vPos = _vOtherDragePrePos;
	pPreItem->SetPos(_vOtherDragePrePos);

	CInventoryMgr::GetInst()->GetInventory()->AddChildUI(pPreItem);


}

void CInterFace::changeItemIndex(CItem* _pItem, CItem* _pOtehr)
{
	int iIndex = GetItemIndex(_pItem);
	int iOtherIndex = GetItemIndex(_pOtehr);

	m_vecItem[iOtherIndex] = _pItem;
	_pItem->m_tItemInfo.m_vPos = _pOtehr->m_tItemInfo.m_vPos;
	_pItem->SetPos(_pOtehr->m_tItemInfo.m_vPos);
}


CItem* CInterFace::getItemThisIndex(int _iIndex)
{
	for (int i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i] == m_vecItem[_iIndex])
			return m_vecItem[i];
	}

	return nullptr;
}

int CInterFace::GetItemIndex(CItem* _pItem)
{
	for (int i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i] == _pItem)
			return i;
	}
	return -1;
}

void CInterFace::DeleteItem(CItem* _pItem)
{
	for (int i = 0; i < m_vecItem.size(); ++i)
	{
		if (m_vecItem[i] == _pItem)
			m_vecItem[i] = nullptr;
	}
}

void CInterFace::ChangeValue(float _HPfValue, float _MPfValue)
{
	if (dynamic_cast<CHP*>(GetChildUI(L"HP")))
	{
		CHP* pHP = dynamic_cast<CHP*>(GetChildUI(L"HP"));
		float fHpValue = ((100.f - _HPfValue) / 100.f) * 88.f;
		pHP->SetMinusHp(fHpValue);
	}
	if (dynamic_cast<CMP*>(GetChildUI(L"MP")))
	{
		CMP* pMP = dynamic_cast<CMP*>(GetChildUI(L"MP"));
		float fValue = ((100.f - _MPfValue) / 100.f) * 88.f;
		pMP->SetMinusMp(fValue);

	}
}


void CInterFace::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();

	//인터페이스 먼저 그리고
	TransparentBlt(_dc,
		(int)vPos.x, (int)vPos.y,
		m_pInterFaceTex->Width(), m_pInterFaceTex->Height(),
		m_pInterFaceTex->GetDC(),
		0, 0,
		m_pInterFaceTex->Width(), m_pInterFaceTex->Height(),
		RGB(0, 0, 0));

	skillRender(_dc);
	keyRender(_dc);


	CUI::render(_dc);

}

void CInterFace::keyRender(HDC _dc)
{

}

void CInterFace::skillRender(HDC _dc)
{
	// 760 655
	Vec2 vStartPos = Vec2(758.f, 655.f);//스킬 아이콘 보여지는 구간
	for (int i = 0; i < 5; ++i)
	{
		//여기에 스킬 아이콘 그리기
		//여기서 스킬 쿨타임 가져오기
		float iSkillTime = CSkillMgr::GetInst()->GetCurSKillTime((SKILL_STATE)i);
		//스킬 쿨타임이 0이면
		if (iSkillTime <= 0.f)
		{
			TransparentBlt(_dc,
				vStartPos.x, vStartPos.y,
				m_vItemStep.x, m_vItemStep.y,
				m_vecSKillTex[i]->GetDC(),
				0, 0,
				m_vecSKillTex[i]->Width(), m_vecSKillTex[i]->Height(),
				RGB(255, 255, 255));
		}
		else
		{
			TransparentBlt(_dc,
				vStartPos.x, vStartPos.y,
				m_vItemStep.x, m_vItemStep.y,
				m_vecCoolDownTex[i]->GetDC(),
				0, 0,
				m_vecCoolDownTex[i]->Width(), m_vecCoolDownTex[i]->Height(),
				RGB(255, 255, 255));


			TransparentBlt(_dc,
				vStartPos.x + 26, vStartPos.y + 10,
				10, 20,
				m_vecNumber[(int)iSkillTime]->GetDC(),
				//시작지점 좌표부터 가져올 이미지 크기
				0, 0,
				m_vecNumber[(int)iSkillTime]->Width(), m_vecNumber[(int)iSkillTime]->Height(),
				RGB(255, 255, 255));
		}
		//다음 이미지 위치 잡기
		vStartPos.x += m_vItemStep.x;
	}
}

