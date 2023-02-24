#include "pch.h"
#include "Header.h"

#include "CObject.h"
#include "CPlayer.h"

#include "AI.h"
#include "CFSM.h"
#include "CEventMgr.h"

#include "CAnimator.h";
#include "CAnimation.h"

//플레이어 상태
#include "CPlayerIdle.h"
#include "CPlayerWalk.h"
#include "CPlayerRun.h"
#include "CPlayerJump.h"
#include "CPlayerJumpAir.h"
#include "CPlayerJumpDown.h"
#include "CPlayerAttack.h"
#include "CPlayerAttackDown.h"
#include "CPlayerJumpAttack.h"
#include "CPlayerSliding.h"
#include "CPlayerHit.h"

void ChangeAIState(AI* _pAI, MONSTER_STATE _eMonState)
{
	tEvent eve = {};
	eve.lParm = (DWORD_PTR)_pAI;//보낼 주소
	eve.wParm = (DWORD_PTR)_eMonState;//다음 상태값
	eve.eEventType = EVENT_TYPE::CHANGE_AI_STATE;

	CEventMgr::GetInst()->AddEvent(eve);
}

void ChangeFSMState(CFSM* _pFSM, PLAYER_STATE _ePlayerState)
{
	tEvent eve = {};
	eve.eEventType = EVENT_TYPE::CHANGE_FSM_STATE;
	eve.lParm = (DWORD_PTR)_pFSM;
	eve.wParm = (DWORD_PTR)_ePlayerState;

	CEventMgr::GetInst()->AddEvent(eve);

}

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent eve = {};
	eve.eEventType = EVENT_TYPE::CREATE_OBJECT;
	eve.lParm = (DWORD_PTR)_pObj;
	eve.wParm = (DWORD_PTR)_eGroup;

	CEventMgr::GetInst()->AddEvent(eve);
}

void DeleteObject(CObject* _pObj)
{
	tEvent eve = {};
	eve.eEventType = EVENT_TYPE::DELETE_OBJECT;
	eve.lParm = (DWORD_PTR)_pObj;

	CEventMgr::GetInst()->AddEvent(eve);
}

void ChangeScene(SCENE_TYPE _eNextScene)
{
	tEvent eve = {};
	eve.eEventType = EVENT_TYPE::SCENE_CHANGE;
	eve.lParm = (DWORD_PTR)_eNextScene;

	CEventMgr::GetInst()->AddEvent(eve);
}

CPlayer* CreatePlayer(Vec2 _vPos)
{
	CPlayer* player = new CPlayer;
	player->SetName(L"Player");
	player->SetTag(GROUP_TYPE::PLAYER);
	player->SetPos(_vPos);
	player->SetScale(Vec2(0.f, 0.f));

	//여기에 fsm에 들어갈 state 넣기

	CFSM* pFSM = new CFSM;
	//player->CreateFSM();
	pFSM->AddState(new CPlayerIdle);
	pFSM->SetCurState(PLAYER_STATE::IDLE);
	pFSM->AddState(new CPlayerWalk);
	pFSM->AddState(new CPlayerRun);
	pFSM->AddState(new CPlayerJump);
	pFSM->AddState(new CPlayerJumpAir);
	pFSM->AddState(new CPlayerJumpDown);
	pFSM->AddState(new CPlayerAttack);
	pFSM->AddState(new CPlayerAttackDown);
	pFSM->AddState(new CPlayerJumpAttack);
	pFSM->AddState(new CPlayerSliding);
	pFSM->AddState(new CPlayerHit);
	player->CreateFSM(pFSM);

	tPlayerInfo tPlayerInfo = {};
	tHitInfo tPlayerHit = {};

	tPlayerInfo.m_fAtt = 10.f;
	tPlayerInfo.m_fSpeed = 200.f;
	tPlayerInfo.m_iHP = 100.f;

	player->SetPlayerInfo(tPlayerInfo);

	return player;
}

void FScanf(char* _pOutBuffer, FILE* _pFile)
{
	int i = 0;
	while (true)
	{
		char c = (char)fgetc(_pFile);
		if (c == '\n')
		{
			_pOutBuffer[i++] = '\0';
			break;
		}
		_pOutBuffer[i++] = c;
	}
}

bool IsFinishAnim(const wstring& _str, CAnimator* _pAnim)
{
	if (_pAnim->GetCurAnimation()->GetName() == _str && !_pAnim->GetCurAnimation()->IsFinish())
	{
		return true;
	}

	return false;
}
