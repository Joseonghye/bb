#include "stdafx.h"
#include "Item.h"
#include "BmpManager.h"
#include "Score.h"
#include "ObjManager.h"
#include "LineManager.h"

CItem::CItem()
{
}
CItem::~CItem()
{
}

void CItem::Initialize()
{
	m_eRenderID = RENDER::OBJECT;
	m_tInfo.iCX = 30;
	m_tInfo.iCY = 30;

	m_iScore = 2000;

}

int CItem::Update()
{
	if (m_bDead) 
	{
		CObj* pObj = CAbstractFactory<CScore>::Create_UI(m_tInfo.fX, m_tInfo.fY, (int)((m_iScore / 1000.f)-1));
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::UI);
		return OBJ::DEAD;
	}
	else
	{
		float fY = 0;
		bool LineCol = CLineManager::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);
		if (LineCol)
		{
			if (fY - (m_tInfo.iCY / 2) > m_tInfo.fY)
			{
				m_tInfo.fY += (0.3f * 9.8f);

				if (m_tInfo.fY >= fY - (m_tInfo.iCY / 2))
				{
					m_tInfo.fY = fY - (m_tInfo.iCY / 2);
				}
			}
		}
		else
			m_tInfo.fY = fY - (m_tInfo.iCY / 2);

	}

	return OBJ::NOEVENT;
}

void CItem::Late_Update()
{
}

void CItem::Render(HDC _DC)
{
	Update_Rect();

	HDC hMemDc = CBmpManager::Get_Instance()->Find_Image(L"Item_banana");
	GdiTransparentBlt(_DC,
		m_tRect.left, m_tRect.top, 
		m_tInfo.iCX, m_tInfo.iCY, 
		hMemDc,
		0, 0, m_tInfo.iCX, m_tInfo.iCY,
		RGB(15, 79, 174));
}

void CItem::Release()
{
}
