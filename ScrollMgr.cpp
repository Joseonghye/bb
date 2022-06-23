#include "stdafx.h"
#include "ScrollMgr.h"


CScrollMgr* CScrollMgr::m_pInstance = nullptr;
CScrollMgr::CScrollMgr()
	: m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock()
{
	if (0 < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCY - (TILECY * TILEY) > m_fScrollY)
		m_fScrollY = WINCY - (TILECY * TILEY);
}
