#pragma once
#ifndef __STAGE_H__
#define __STAGE_H__
#include "Scene.h"

class CObj;
class CStage :
	public CScene
{
public:
	CStage();
	virtual ~CStage();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	bool m_bNext;
	float m_fY;
	DWORD m_dwTime;

	float m_iStage;
};

#endif // !__STAGE_H__