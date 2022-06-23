#pragma once
#ifndef __BMPMANAGER_H__
#define __BMPMANAGER_H__

class CMyBitmap;
class CBmpManager
{
private:
	CBmpManager();
	~CBmpManager();

	void Release();

public:
	static CBmpManager* Get_Instance()
	{
		if(!m_pInstance)
			m_pInstance = new CBmpManager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

	void Insert_Bmp(const TCHAR* _pFilePath, const TCHAR* _pFrameKey);
	HDC Find_Image(const TCHAR* _pFrameKey);

private:
	static CBmpManager* m_pInstance;
	map<const TCHAR*, CMyBitmap*>	m_mapBit;

};

#endif // __BMPMANAGER_H__
