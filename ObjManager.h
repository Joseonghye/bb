#pragma once
#ifndef __OBJMANAGER_H__
#define __OBJMANAGER_H__

class CObj;
class CObjManager
{
private:
	CObjManager();
	~CObjManager();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

	void Add_Obj(CObj* pObj, OBJID::ID _id);
	void Set_Score(int _score) { m_iScore += _score; }
	void Set_Life() { m_iLife--; }

	int Get_Life() { return m_iLife; }
	bool Get_Next() { return (m_pObjList[OBJID::MONSTER].empty() && m_pObjList[OBJID::BUBBLE_MONSTER].empty()); }
	 CObj* Get_Player() { return m_pObjList[OBJID::PLAYER].front(); }
	void Delete_Player()
	{
		if (!m_pObjList[OBJID::PLAYER].empty())
		{
		
		SAFE_DELETE(m_pObjList[OBJID::PLAYER].front());
		m_pObjList[OBJID::PLAYER].clear();
		}
	}

	void Save_BLANK();
	void Load_BLANK();
	
	void Set_Stage();

	void Render_ID(HDC _DC, OBJID::ID _id);

public:
	static CObjManager* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjManager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	void Update_Score();

private:
	static CObjManager* m_pInstance;
	list<CObj*> m_pObjList[OBJID::END];

	int m_iScore;
	int m_iLife;
};

#endif // !__OBJMANAGER_H__