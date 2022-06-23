#pragma once
#include "Obj.h"
class CBall :
	public CObj
{
public:
	enum STATE{WALK,DEAD,END};
public:
	CBall();
	virtual ~CBall();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	void Change_State();
	virtual void Update_Frame() override;

private:
	STATE	m_eCurState;
	STATE	m_ePreState;
};

