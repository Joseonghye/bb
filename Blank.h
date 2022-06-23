#pragma once
#include "Obj.h"
class CBlank :
	public CObj
{
public:
	CBlank();
	virtual ~CBlank();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

