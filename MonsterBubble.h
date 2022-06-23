#pragma once
#include "Bubble.h"
class CMonsterBubble :
	public CBubble
{
public:
	CMonsterBubble();
	virtual ~CMonsterBubble();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _DC) override;

private:
	void Move_Dead();
	void Change_State();
	virtual void Update_Frame() override;

private:
	float m_fX;
	float m_fY;
};

