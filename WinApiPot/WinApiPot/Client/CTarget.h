#pragma once
#include "CObject.h"

class CFire;

class CTarget :
    public CObject
{
public:
	CTarget();
	virtual ~CTarget();

private:
	CTexture* m_pTargetTex;

	void move(Vec2 _vForce);
public:
	virtual void render(HDC _dc);
	virtual void update();
	virtual void finalupdate();


	friend class CFire;
};

