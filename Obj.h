#pragma once

#ifndef __OBJ_H__
#define __OBJ_H__

class CObj
{

public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;

public:
	void Set_Pos(float x, float y) { m_tInfo.fX = x; m_tInfo.fY = y; }
	void Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void Set_Dead() { m_bDead = true; }
	void Set_Super() { m_bSuper = true; }
	void Set_PosX(float x) { m_tInfo.fX += x; }
	void Set_PosY(float y) { m_tInfo.fY += y; }
	void Set_Dir(DIRECT::DIR _dir) { m_eDir = _dir; }
	void Reverse_Dir() { (m_eDir == DIRECT::LEFT) ? (m_eDir = DIRECT::RIGHT) : (m_eDir = DIRECT::LEFT); }
	void Set_Coll() { m_bColl = true; }

public:
	const RECT& Get_Rect() const { return m_tRect; }
	 INFO& Get_Info()  { return m_tInfo; }
	const bool& Get_Dead() const { return m_bDead; }
	const bool& Get_Super() const { return m_bSuper;}
	const RENDER::ID& Get_RenderID() const { return m_eRenderID; }
	const int& Get_DrawID() const { return m_iDrawID; }
	const int& Get_Score() const { return m_iScore; }


protected:
	void Update_Rect();
	virtual void Update_Frame();

protected:
	INFO	m_tInfo;
	RECT	m_tRect;


	RENDER::ID		m_eRenderID;
	int m_iDrawID;
	int m_iScore;

	float	m_fSpeed;
	
	bool	m_bDead;
	bool	m_bSuper;
	bool	m_bColl;

	FRAME	m_tFrame;
	DIRECT::DIR m_eDir;

};


#endif // !__OBJ_H__
