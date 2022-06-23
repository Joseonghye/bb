#include "stdafx.h"
#include "Player.h"
#include "BmpManager.h"
#include "Bubble.h"
#include "ObjManager.h"
#include "LineManager.h"
#include "ScrollMgr.h"

CPlayer::CPlayer()
	:m_eCurState(END), m_ePreState(END),
	m_dwBubble(0), m_dwJump(0), m_bKey(true), 
	m_bJump(false), m_fJumpPower(0.f), m_fJumpTime(0.f), m_fJumpY(0.f)
{
}
CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_eRenderID = RENDER::OBJECT;

	m_eDir = DIRECT::RIGHT;

	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_fSpeed = 5.f;
	m_fJumpPower = 40.f;

	m_bSuper = false;
	m_eCurState = IDLE;
	m_tFrame.iStartX = 0;
	m_tFrame.iStartY = 0;

	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Player.bmp", L"Player");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Player/Stretch.bmp", L"Stretch");
}

int CPlayer::Update()
{
	if (m_tInfo.fY >= 512)
		m_tInfo.fY = 0.f;

	if (m_bDead)
	{
		m_eCurState = DEAD;
		m_bJump = false;
		m_bSuper = true;
		m_dwTime = GetTickCount();
	}
	else
		Key_Check();

	if (m_bSuper && m_dwTime + 5000 <= GetTickCount())
		m_bSuper = false;
	
	if (m_bJump)
		m_eCurState = JUMP;

	Jumping();
	Change_State();
	
	Update_Frame();
	Update_Rect();
	return OBJ::NOEVENT;
}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC _DC)
{
	HDC hMemDc = CBmpManager::Get_Instance()->Find_Image(L"Player");
	float scrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_eDir == DIRECT::RIGHT) 
	{
		GdiTransparentBlt(_DC, 
			m_tRect.left, m_tRect.top,
			m_tInfo.iCX, m_tInfo.iCY,
			hMemDc,
			m_tFrame.iStartX * m_tInfo.iCX, m_tFrame.iStartY * m_tInfo.iCY,
			m_tInfo.iCX, m_tInfo.iCY,
			RGB(4, 2, 4));
	}
	else
	{
		HDC hStretchDC = CBmpManager::Get_Instance()->Find_Image(L"Stretch");
		StretchBlt(hStretchDC
			, 0, 0
			, m_tInfo.iCX, m_tInfo.iCY
			, hMemDc
			, m_tFrame.iStartX *  m_tInfo.iCX + m_tInfo.iCX, m_tFrame.iStartY *  m_tInfo.iCY
			, -m_tInfo.iCX, m_tInfo.iCY
			, SRCCOPY);

		GdiTransparentBlt(_DC
			, m_tRect.left, m_tRect.top
			, m_tInfo.iCX, m_tInfo.iCY
			, hStretchDC
			, 0, 0
			, m_tInfo.iCX, m_tInfo.iCY
			, RGB(4, 2, 4));
	}
}

void CPlayer::Release()
{
}

void CPlayer::Key_Check()
{
	

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_eDir = DIRECT::LEFT;
		m_tInfo.fX -= m_fSpeed;
		m_eCurState = WALK;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_eDir = DIRECT::RIGHT;
		m_tInfo.fX += m_fSpeed;
		m_eCurState = WALK;
	}
	else
		m_eCurState = IDLE;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_dwBubble + 180 < GetTickCount())
		{
			m_dwBubble = GetTickCount();


			CObj* pObj = CAbstractFactory<CBubble>::Create(m_tInfo.fX, m_tInfo.fY);
			pObj->Set_Dir(m_eDir);
			pObj->Set_Super();
			CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::BUBBLE);
			m_eCurState = ATTACK;
		}
	}
	else
		m_eCurState = IDLE;

	//มกวม
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (!m_bJump)
			m_fJumpY = m_tInfo.fY;


		if (m_bKey) 
		{
			m_bJump = true;
			m_eCurState = JUMP;
			m_bKey = false;
		}
	}
	else
	{
		m_bKey = true;
	}
}

void CPlayer::Jumping()
{
	float fY = 0;
	bool LineCol = CLineManager::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	if (m_bJump)
	{
		m_fJumpTime += 0.2f;
		m_tInfo.fY = m_fJumpY - ((m_fJumpPower * m_fJumpTime) - (0.5f * 9.8f * m_fJumpTime*m_fJumpTime));

		if (LineCol && m_tInfo.fY >= fY - (m_tInfo.iCY / 2))
		{
			m_bJump = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = fY - (m_tInfo.iCY / 2);
			m_eCurState = IDLE;
		}
	}
	else if (LineCol)
	{

		if (fY - (m_tInfo.iCY / 2) > m_tInfo.fY)
		{
			m_eCurState = DOWN;
			m_tInfo.fY += (0.3f * 9.8f);

			if (m_tInfo.fY >= fY - (m_tInfo.iCY / 2))
			{
				m_tInfo.fY = fY - (m_tInfo.iCY / 2);
				m_eCurState = IDLE;
			}
		}
		else
			m_tInfo.fY = fY - (m_tInfo.iCY / 2);

		//m_eCurState = DOWN;
		//m_tInfo.fY -= (0.5f * 9.8f);

		//if (m_tInfo.fY >= fY - (m_tInfo.iCY / 2))
		//{
		//	m_tInfo.fY = fY - (m_tInfo.iCY / 2);
		//	m_eCurState = IDLE;
		//}
	}

}

void CPlayer::Change_State()
{
	if (m_ePreState != m_eCurState)
	{
		m_ePreState = m_eCurState;

		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 2;
			m_tFrame.iStartY = IDLE;
			m_tFrame.dwDelayTime = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case WALK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 2;
			m_tFrame.iStartY = WALK;
			m_tFrame.dwDelayTime = 150;
			m_tFrame.dwTime = GetTickCount();
			break;
		case JUMP:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 4;
			m_tFrame.iStartY = JUMP;
			m_tFrame.dwDelayTime = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case DOWN:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 1;
			m_tFrame.iStartY = DOWN;
			m_tFrame.dwDelayTime = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 1;
			m_tFrame.iStartY = ATTACK;
			m_tFrame.dwDelayTime = 10;
			m_tFrame.dwTime = GetTickCount();
			break;
		case DEAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 6;
			m_tFrame.iStartY = DEAD;
			m_tFrame.dwDelayTime = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
	}
}

void CPlayer::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelayTime < GetTickCount())
	{
		++m_tFrame.iStartX;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
		{
			m_tFrame.iStartX = 0;
			if (m_eCurState == DEAD)
			{
				if (CObjManager::Get_Instance()->Get_Life() > 0) 
				{
					m_tInfo.fX = 40;
					m_tInfo.fY = 394;
					m_eCurState = IDLE;
					m_bDead = false;
				}
			}
		}
	}
}
