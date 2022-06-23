#include "stdafx.h"
#include "Blank.h"
#include "ScrollMgr.h"
CBlank::CBlank()
{
}
CBlank::~CBlank()
{
}

void CBlank::Initialize()
{
	m_tInfo.iCX = TILECX;
	m_tInfo.iCY = TILECY;
}

int CBlank::Update()
{
	Update_Rect();
	return 0;
}

void CBlank::Late_Update()
{
}

void CBlank::Render(HDC _DC)
{
	//float ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
//	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBlank::Release()
{
}
