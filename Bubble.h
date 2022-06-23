#pragma once
#ifndef __BUBBLE_H_
#define __BUBBLE_H_

#include "Obj.h"
class CBubble :
	public CObj
{
public:
	enum STATE { START, BLUE, PINK,RED, BLANK,POP, END };
public:
	CBubble();
	virtual ~CBubble();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	void Set_bUp(bool _up) { m_bUp = _up; }
	void Set_bCenter() { m_bCenter = true; }

protected:
	virtual void Update_Frame() override;
	void Move_Wall();
private:
	void Change_State();
	

protected:
	DWORD m_time;

	bool m_bUp;
	bool m_bCenter;
	bool m_bRealDead;
	bool m_bStop[2];

	STATE	m_eCurState;
	STATE	m_ePreState;

	
};

#endif // !__BUBBLE_H_