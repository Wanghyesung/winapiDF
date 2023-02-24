#pragma once

class AI;
class CObject;
class CPlayer;
class CAnimator;

class CFSM;

void ChangeAIState(AI* _pAI, MONSTER_STATE _eMonState);
void ChangeFSMState(CFSM* _pFSM, PLAYER_STATE _ePlayerState);
void DeleteObject(CObject* _pObj);
void ChangeScene(SCENE_TYPE _eNextScene);

CPlayer* CreatePlayer(Vec2 _vPos);

template <typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (int i = 0; i < _vec.size(); ++i)
	{
		if(_vec[i] != nullptr)
			delete _vec[i];
	}
	_vec.clear();
}

template <typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();
	
	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	_map.clear();
}

void FScanf(char* _pOutBuffer, FILE* _pFile);

bool IsFinishAnim(const wstring& _str, CAnimator* _pAnim);
void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);