#pragma once
#include "Scene.h"
class CEnding :
	public CScene
{
public:
	CEnding();
	virtual ~CEnding();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

