#pragma once
#include "Monster.h"
class CMighta :
	public CMonster
{
public:
	CMighta();
	virtual ~CMighta();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _DC) override;

private:
	virtual void Move() override;
	virtual void Change_State() override;

private:
	CObj* m_pBall;
};

