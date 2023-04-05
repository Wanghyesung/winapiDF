#pragma once

class CFSM;
class CSound;

class CPlayerState
{
public:
	CPlayerState(PLAYER_STATE ePlayerState);
	virtual ~CPlayerState();


public:
	PLAYER_STATE GetType() { return m_ePlayerState; }

	void SetCurFrame(int _iCurFrame) { m_iCurFrame = _iCurFrame; }
	int GetCurFrame() { return m_iCurFrame; }
	void InitZeroFrame() { m_iCurFrame = 0; }

public:
	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit();

	CFSM* GetFSM() { return m_pOwner; }

protected:
	void SetAnimSound(const wstring& _strPath);
	CSound* GetAnimSound() { return m_pSound; }

private:
	PLAYER_STATE m_ePlayerState;
	CFSM* m_pOwner;

	int m_iCurFrame;

	CSound* m_pSound;

	friend class CFSM;
};

