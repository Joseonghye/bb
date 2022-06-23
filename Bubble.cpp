#include "stdafx.h"
#include "Bubble.h"
#include "BmpManager.h"

CBubble::CBubble()
	:m_eCurState(END), m_ePreState(END), m_time(0), m_bUp(false), m_bCenter(false), m_bRealDead(false)
{
}
CBubble::~CBubble()
{
	Release();
}

void CBubble::Initialize()
{
	m_eRenderID = RENDER::OBJECT;

	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_eCurState = START;

	m_fSpeed = 7.f;
	m_iScore = 20;

	m_time = GetTickCount();

	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Bubble.bmp", L"Bubble");
}

int CBubble::Update()
{
	if (m_bRealDead)
		return OBJ::DEAD;

	if (m_bDead)
		m_eCurState = POP;
	else 
	{
		if (m_time + 21000 < GetTickCount())
			m_eCurState = POP;
		else if (m_time + 20000 < GetTickCount())
			m_eCurState = BLANK;
		else if (m_time + 18000< GetTickCount())
			m_eCurState = RED;
		else if (m_time + 15000< GetTickCount())
			m_eCurState = PINK;
		else if (m_time + 9000< GetTickCount())
			m_eCurState = BLUE;
		
	}

	if (m_tInfo.fY <= 50)
		m_tInfo.fY = 520;

	Move_Wall();

	if (m_bSuper &&m_time+ 500 < GetTickCount() ) m_bSuper = false;
	
	Change_State();

	Update_Frame();
	Update_Rect();

	return OBJ::NOEVENT;
}

void CBubble::Late_Update()
{
}

void CBubble::Render(HDC _DC)
{
	HDC hMemDc= CBmpManager::Get_Instance()->Find_Image(L"Bubble");
	GdiTransparentBlt(_DC,
		m_tRect.left, m_tRect.top,
		m_tInfo.iCX, m_tInfo.iCY,
		hMemDc,
		m_tFrame.iStartX * m_tInfo.iCX, m_tFrame.iStartY * m_tInfo.iCY,
		m_tInfo.iCX, m_tInfo.iCY,
		RGB(15, 79, 174));
}

void CBubble::Release()
{
}

void CBubble::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelayTime < GetTickCount())
	{
		++m_tFrame.iStartX;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
		{
			m_tFrame.iStartX = 0;
			if (m_eCurState == POP)
				m_bRealDead = true;
		}
	}
}

void CBubble::Change_State()
{
	if (m_ePreState != m_eCurState)
	{
		m_ePreState = m_eCurState;
		switch (m_eCurState)
		{
		case START:
			m_tFrame.iStartY = START;
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 3;
			m_tFrame.dwDelayTime = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case BLUE:
			m_tFrame.iStartY = BLUE;
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 3;
			m_tFrame.dwDelayTime = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case PINK:
			m_tFrame.iStartY = PINK;
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 3;
			m_tFrame.dwDelayTime = 200;
			m_tFrame.dwTime = GetTickCount();
		case RED:
			m_tFrame.iStartY = RED;
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 3;
			m_tFrame.dwDelayTime = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case BLANK:
			m_tFrame.iStartY = BLANK;
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 3;
			m_tFrame.dwDelayTime = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case POP:
			m_tFrame.iStartY = POP;
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 1;
			m_tFrame.dwDelayTime = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		
		}
	}
}

void CBubble::Move_Wall()
{
	if (m_bCenter)
	{
		if (m_tInfo.fX > (WINCX / 2)+1.f || m_tInfo.fX < (WINCX / 2) + 1.f)
		{
			if (m_eDir == DIRECT::RIGHT)
				m_tInfo.fX += m_fSpeed;
			else if (m_eDir == DIRECT::LEFT)
				m_tInfo.fX -= m_fSpeed;
		}
	}
	else
	{
		if (m_bUp)
		{
			if(m_fSpeed != 3.f)
				m_fSpeed = 3.f;
			m_tInfo.fY -= m_fSpeed;
		}
		else if (m_eDir == DIRECT::RIGHT)
			m_tInfo.fX += m_fSpeed;
		else if (m_eDir == DIRECT::LEFT)
			m_tInfo.fX -= m_fSpeed;
	}
}
