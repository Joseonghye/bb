#pragma once
#ifndef __TILEMANAGER_H__
#define __TILEMANAGER_H__

class CObj;
class CTileManager
{
public:
	CTileManager();
	~CTileManager();

public:
	void Initialize();
	void Release();
	void Render(HDC _DC);

public:
	void Picking_Tile(int _iDrawID);
	void Add_Rect();

public:
	void Save_Tile();
	void Load_Tile();

public:
	static CTileManager* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTileManager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CTileManager*	m_pInstance;
	vector<CObj*>		m_vecTile;


};

#endif // !__TILEMANAGER_H__