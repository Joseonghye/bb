#pragma once
#include "Scene.h"
class CMyEdit :
	public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	bool m_bChcek;
	bool m_bBlank;
	int num;
};

