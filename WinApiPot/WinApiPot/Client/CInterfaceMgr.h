#pragma once

class CInterFace;

class CInterfaceMgr
{
	SINGLE(CInterfaceMgr);

public:
	void ChangeInterFaceValue(float _fHPValue, float _fMPValue);

public:
	void SetInterFace(CInterFace* _pInterFace) { m_pPlayerInterFace = _pInterFace; }

private:
	CInterFace* m_pPlayerInterFace;

	
};

