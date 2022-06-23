#include "stdafx.h"
#include "Ball.h"
#include "BmpManager.h"

CBall::CBall()
	:m_eCurState(END),m_ePreState(END)
{
}

CBall::~CBall()
{
	Release();
}

void CBall::Initialize()
{
	m_bColl = false;
	m_eRenderID = RENDER::OBJECT;

	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;
	m_fSpeed = 6.f;

	m_eCurState = WALK;
}

int CBall::Update()
{
	if (m_bDead)
		return OBJ::DEAD;

	if (m_eDir == DIRECT::LEFT)
		m_tInfo.fX -= m_fSpeed;
	else
		m_tInfo.fX += m_fSpeed;

	Change_State();
	Update_Frame();
	Update_Rect();

	return OBJ::NOEVENT;
}

void CBall::Late_Update()
{
	if (m_bColl)
	{
		m_eCurState = DEAD;
	}
}

void CBall::Render(HDC _DC)
{
	HDC hMemDc = CBmpManager::Get_Instance()->Find_Image(L"Ball");
	GdiTransparentBlt(_DC,
		m_tRect.left, m_tRect.top,
		m_tInfo.iCX, m_tInfo.iCY,
		hMemDc,
		m_tFrame.iStartX * m_tInfo.iCX, m_tFrame.iStartY * m_tInfo.iCY,
		m_tInfo.iCX, m_tInfo.iCY,
		RGB(4, 2, 4));
}

void CBall::Release()
{
}

void CBall::Change_State()
{
	if (m_ePreState != m_eCurState)
	{
		m_ePreState = m_eCurState;
		switch (m_eCurState)
		{
		case WALK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 4;
			m_tFrame.iStartY = WALK;
			m_tFrame.dwDelayTime = 150;
			m_tFrame.dwTime = GetTickCount();
			break;
		case DEAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 2;
			m_tFrame.iStartY = DEAD;
			m_tFrame.dwDelayTime = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
	}
}

void CBall::Update_Frame()
{

	if (m_tFrame.dwTime + m_tFrame.dwDelayTime < GetTickCount())
	{
		++m_tFrame.iStartX;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
		{
			m_tFrame.iStartX = 0;

			if (m_eCurState == DEAD)
				m_bDead = true;
		}
	}
}
