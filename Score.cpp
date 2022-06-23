#include "stdafx.h"
#include "Score.h"
#include "BmpManager.h"

CScore::CScore():m_dwTime(0)
{
}
CScore::~CScore()
{
	Release();
}

void CScore::Initialize()
{
	m_eRenderID = RENDER::UI;
	m_tInfo.iCX = 45;
	m_tInfo.iCY = 35;
	m_dwTime = GetTickCount();
}

int CScore::Update()
{
	if (m_bDead)
		return OBJ::DEAD;

	if (m_dwTime + 1000 > GetTickCount())
	{
		m_tInfo.fY -= 1.f;
	}
	else if (m_dwTime + 1500 < GetTickCount())
		m_bDead = true;

	Update_Rect();
	return OBJ::NOEVENT;
}

void CScore::Late_Update()
{
}

void CScore::Render(HDC _DC)
{
	HDC hMemDc = CBmpManager::Get_Instance()->Find_Image(L"Score_1000");

	GdiTransparentBlt(_DC,
		m_tRect.left, m_tRect.top,
		m_tInfo.iCX, m_tInfo.iCY,
		hMemDc,
		m_iDrawID * m_tInfo.iCX, 0,
		m_tInfo.iCX, m_tInfo.iCY,
		RGB(4, 2, 4));
}



void CScore::Release()
{
}
