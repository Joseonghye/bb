#pragma once
class CUI
{
public:
	CUI();
	virtual ~CUI();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;

public:
	void Set_Pos(float _x, float _y) { m_tInfo.fX = _x; m_tInfo.fY = _y; }
	void Set_Type(int _type) { m_iType = _type; }

protected:
	void Update_Rect();

protected:
	INFO m_tInfo;
	RECT m_tRect;

	RENDER::ID m_eRenderID;

	bool m_bDead;

	int m_iType;

	int m_iStartX;
	int m_iStartY;

};

