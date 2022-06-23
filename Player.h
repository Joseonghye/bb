#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	enum STATE { IDLE, WALK, JUMP, DOWN,ATTACK, DEAD, END };
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	void Key_Check();
	void Jumping();
	void Change_State();

	virtual void Update_Frame() override;

private:
	STATE	m_eCurState;
	STATE	m_ePreState;

	DWORD m_dwBubble;
	DWORD m_dwJump;
	DWORD m_dwTime;

	bool		m_bJump;
	bool		m_bKey;
	float		m_fJumpPower;
	float		m_fJumpTime;
	float		m_fJumpY;

};

