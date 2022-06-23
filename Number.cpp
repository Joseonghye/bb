#include "stdafx.h"
#include "Number.h"
#include "BmpManager.h"

CNumber::CNumber()
{
}


CNumber::~CNumber()
{
}

void CNumber::Initialize()
{
	m_eRenderID = RENDER::UI;
	m_tInfo.iCX = 25;
	m_tInfo.iCY = 30;
}

int CNumber::Update()
{
	Update_Rect();
	return OBJ::NOEVENT;
}

void CNumber::Late_Update()
{
}

void CNumber::Render(HDC _DC)
{
	HDC hMemDc = CBmpManager::Get_Instance()->Find_Image(L"Number");

	GdiTransparentBlt(_DC,
		m_tRect.left, m_tRect.top,
		m_tInfo.iCX, m_tInfo.iCY,
		hMemDc,
		m_iDrawID* m_tInfo.iCX, 0,
		m_tInfo.iCX, m_tInfo.iCY,
		RGB(4, 2, 4));
}

void CNumber::Release()
{
}
