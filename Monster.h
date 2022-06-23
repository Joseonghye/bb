#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	enum STATE { WALK, ANGRY,AROUND,ANGRY_AROUND, END };
public:
	CMonster();
	virtual ~CMonster();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	void Set_Angry() { m_eCurState = ANGRY; }

protected:
	virtual void Move();
	virtual void Change_State();
	void Jumping();
	
	virtual void Update_Frame() override;

protected:
	STATE	m_eCurState;
	STATE	m_ePreState;

	CObj*	m_pTarget;
	bool m_bTarget;
	float m_fX;

	float m_fAngry;
	DWORD m_dwTime;

	DWORD m_dwJump;
	bool m_bAround;
	int m_iDist;

	bool		m_bJump;
	float		m_fJumpPower;
	float		m_fJumpTime;
	float		m_fJumpY;

	bool m_bDown;
};

