#include "stdafx.h"
#include "Tile.h"
#include "BmpManager.h"
#include "ScrollMgr.h"
CTile::CTile()
{
}
CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_eRenderID = RENDER::BACKGROUND;

	m_tInfo.iCX = TILECX;
	m_tInfo.iCY = TILECY;
}

int CTile::Update()
{
	return 0;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC _DC)
{
	Update_Rect();

	float ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Tile");
	BitBlt(_DC
		, m_tRect.left, m_tRect.top+ScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_iDrawID * TILECX, 0
		, SRCCOPY);
}

void CTile::Release()
{
}
