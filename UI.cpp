#include "stdafx.h"
#include "UI.h"


CUI::CUI()
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
}
CUI::~CUI()
{
}

void CUI::Update_Rect()
{
	m_tRect.left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));

}
