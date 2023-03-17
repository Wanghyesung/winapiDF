#pragma once
#include "CObject.h"

class CCollider;
class CSkill;
class CPlayerState;
class CBullet;
class CFSM;


struct tPlayerInfo
{
    float       m_fSpeed;   //�ӵ�
    float       m_fHP;      //ü��
    float       m_fMP;      //����
    float       m_fAtt;     //���ݷ�
    float       m_AccHP;
};

class CTexture;
class CAnimator;

class CPlayer :
    public CObject
{
   
private:
    PLAYER_STATE playerCurState;
    PLAYER_STATE playerPrevState; //���� ���°�

    SKILL_STATE playerCurSkill;

    CFSM* m_pFSM;

    static tPlayerInfo  m_tPlayerInfo;
    tHitInfo m_tPlayerHit;

    static int m_iDirX;     //���� ����
    int m_prevDirX;
    static int m_iDirY;
    int m_prevDirY;

    bool m_bOnSkill;

    static UINT m_iKeyStack;
    static UINT m_iPrePushKey;
    static UINT m_iCurPushKey;
    float m_fCurTime;
    float m_fRunTime;
    bool m_bIsOnDobuleKey;

    float m_fCurAccTime;
    float m_fAccTime;

    CTexture* m_pBullet;
    CTexture* m_pFireMotion;

    CSkill* m_pSkill;

public:
    CPlayer();
    virtual ~CPlayer();

    void CreateFSM(CFSM* _pFSM);

    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);

    void CreateBullet(CPlayer* _pPlayer, ATTACK_TYPE _eAttType = ATTACK_TYPE::NORMAL);

    void updateState();
    void updateSkillState();

    bool IsOnDobuleKey() { return m_bIsOnDobuleKey; }

public:
    virtual void OnColliderEnter(CCollider* _pOther);
    virtual void OnColliderExit(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);

public:
    void SetPlayerInfo(const tPlayerInfo& _tPlayerInfo) { m_tPlayerInfo = _tPlayerInfo; }
    void SetPlayerHitInfo(const tHitInfo& _tHitInfo) { m_tPlayerHit = _tHitInfo; }

    int GetPlayerDirX() { return m_iDirX; }
    int GetPlayerDirY() { return m_iDirY; }

    void SetPlayerDirX(int _iDir) { m_iDirX = _iDir; }
    void SetPlayerDirY(int _iDir) { m_iDirY = _iDir; }

    void HitPlayer(CCollider* _pOther, const tAttackInfo& _tAttInfo);
    //�������϶� �ǰ��� ������ �� ������ġ�� �´��� Ȯ��
    bool IsSameJumLoc(CCollider* _pOther, CCollider* _pThis);

public:
    void CreateSkill();
    CSkill* GetSkill() { return m_pSkill; }

private:
    void update_doubleKey();
    void update_InterFace();
    PLAYER_STATE GetPrevState() { return playerPrevState; }
    void SetPrevState(PLAYER_STATE _eState) { playerPrevState = _eState; }


    friend class CBullet;
    friend class CFSM;
    friend class CPlayerHit;
    friend class CPlayerHitUpper;
    friend class CSkillMgr;
};

