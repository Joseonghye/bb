#pragma once
#include "Obj.h"
class CNumber :
	public CObj
{
public:
	CNumber();
	virtual ~CNumber();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

