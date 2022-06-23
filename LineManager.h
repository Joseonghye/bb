#pragma once
#ifndef __LINEMANAGER_H__
#define __LINEMANAGER_H__

class CLine;
class CLineManager
{
private:
	CLineManager();
	~CLineManager();

public:
	void Initialize();
	void Render(HDC _DC);
	void Release();

	void Draw_Line();

	void Save_Line();
	void Load_Line();

	void Set_Stage();

public:
	bool Collision_Line(float _x, float _y, float* _fY);

public:
	static CLineManager* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineManager;

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}
	

private:
	static CLineManager* m_pInstance;
	list<CLine*> m_pLineList;

	int iY;
	POINT m_LinePt[2];
	bool m_bCheck;
};

#endif // !__LINEMANAGER_H__
