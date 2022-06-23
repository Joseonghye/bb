#include "stdafx.h"
#include "BmpManager.h"
#include "MyBitmap.h"

CBmpManager* CBmpManager::m_pInstance = nullptr;

CBmpManager::CBmpManager()
{
}
CBmpManager::~CBmpManager()
{
	Release();
}

void CBmpManager::Release()
{
	for (auto& pair : m_mapBit)
		SAFE_DELETE(pair.second);
	m_mapBit.clear();
}

void CBmpManager::Insert_Bmp(const TCHAR * _pFilePath, const TCHAR * _pFrameKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CStrCmp(_pFrameKey));

	if (m_mapBit.end() == iter)
	{
		CMyBitmap*	pBmp = new CMyBitmap;
		pBmp->Load_Bmp(_pFilePath);

		m_mapBit.emplace(_pFrameKey, pBmp);
	}
}

HDC CBmpManager::Find_Image(const TCHAR * _pFrameKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CStrCmp(_pFrameKey));

	if (m_mapBit.end() == iter)
		return nullptr;

	return iter->second->Get_DC();
}
