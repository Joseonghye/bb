#include "stdafx.h"
#include "MonsterBubble.h"
#include "BmpManager.h"
#include "Item.h"
#include "ObjManager.h"
#include "Monster.h"
#include "Mighta.h"

CMonsterBubble::CMonsterBubble() :m_fX(0), m_fY(0)
{
	m_bStop[0] = false;
	m_bStop[1] = false;
}
CMonsterBubble::~CMonsterBubble()
{
	Release();
}

void CMonsterBubble::Initialize()
{
	m_eRenderID = RENDER::OBJECT;
	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_iScore = 1000;

	m_eCurState = START;
	m_bSuper = false;
	m_bUp = true;

	m_fSpeed = 7.f;
	m_time = GetTickCount();

	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Bubble_Monster.bmp", L"Bubble_Monster");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Bubble_Monster2.bmp", L"Bubble_Monster2");
}

int CMonsterBubble::Update()
{
	if (m_bRealDead)
	{
		CObj* pObj = CAbstractFactory<CItem>::Create(m_fX,m_fY);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::ITEM);

		return OBJ::DEAD;
	}
	if (m_bDead) 
	{
		if (m_fX == 0)
		{
			m_fX = (float)(rand() % 450 + 50);
			m_fY = (float)(rand() % 400 + 90);

			if (m_fX < 32.f+m_tInfo.iCX)
				m_fX = + m_tInfo.iCX;
			else if (m_fX > WINCX - (m_tInfo.iCX+32.f))
				m_fX = WINCX - (m_tInfo.iCX + 32.f);

			if (m_fY > WINCY - (m_tInfo.iCY+ 32.f))
				m_fY = WINCY - (m_tInfo.iCY + 32.f);

			m_fSpeed = 5;
		}
		m_eCurState = BLANK;

		Move_Dead();
	}
	else
	{
		if (m_time + 15000 < GetTickCount())
		{//화난 몬스터 
			if (m_iDrawID == 1) {
				CObj* pObj = CAbstractFactory<CMonster>::Create_AngryMonster(m_tInfo.fX, m_tInfo.fY);
				CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);
			}
			else
			{
				CObj* pObj = CAbstractFactory<CMighta>::Create_AngryMonster(m_tInfo.fX, m_tInfo.fY);
				CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);
			}

			return OBJ::DEAD;
		}
		if (m_time + 13000< GetTickCount())
			m_eCurState = RED;
		else if (m_time + 10000< GetTickCount())
			m_eCurState = PINK;
		else if (m_time + 6000< GetTickCount())
			m_eCurState = BLUE;

		if (m_tInfo.fY <= 50)
			m_tInfo.fY = 520;

		 Move_Wall();
	}

	Change_State();

	Update_Frame();
	Update_Rect();

	return OBJ::NOEVENT;
}

void CMonsterBubble::Render(HDC _DC)
{
	HDC hMemDc;
	if(m_iDrawID == 1)
		hMemDc = CBmpManager::Get_Instance()->Find_Image(L"Bubble_Monster");
	else 
		hMemDc = CBmpManager::Get_Instance()->Find_Image(L"Bubble_Monster2");

	GdiTransparentBlt(_DC,
		m_tRect.left, m_tRect.top,
		m_tInfo.iCX, m_tInfo.iCY,
		hMemDc,
		m_tFrame.iStartX * m_tInfo.iCX, m_tFrame.iStartY * m_tInfo.iCY,
		m_tInfo.iCX, m_tInfo.iCY,
		RGB(15, 79, 174));
}


void CMonsterBubble::Move_Dead()
{
	//bool LineCol = CLineManager::Get_Instance()->Collision_Line(m_fX,m_fY, &m_fY);
	if(m_bColl)
		m_bRealDead = true;

	float speed = 5.f;
	float _x = m_fX - m_tInfo.fX;
	if (_x < 0)
	{
		speed *= -1;
	}

	m_tInfo.fX += speed;

	if (abs(_x) <= 20)
		m_bStop[0] = true;

	speed = 5.f;

	float _y = m_fY - m_tInfo.fY;
	if (_y < 0)
	{
		speed *= -1;
	}
	m_tInfo.fY += speed;
		
	if(abs(_y) <= 20)
		m_bStop[1] = true;

	if (m_bStop[0] && m_bStop[1])
			m_bRealDead = true;

	//if (m_fY > WINCY - (m_tInfo.iCX + 32.f))
	//	m_fY = WINCY - (m_tInfo.iCX + 32.f);

	//float fX = m_tInfo.iCX - (float)m_fX;
	//float fY = m_tInfo.iCY - (float)m_fY;
	//float fDia = sqrtf(fX * fX + fY * fY);

	//float	fRad = acosf(fX / fDia);
	//float m_fAngle = fRad * 180.f / PI;

	////if (iY >= m_tInfo.fY)
	////	m_fAngle *= -1.f;

	//if (m_tInfo.fX <(m_fX - m_fSpeed) || m_tInfo.fX >(m_fX + m_fSpeed))
	//	m_tInfo.fX += sinf(m_fAngle * PI / 180.f) * m_fSpeed;
	//else
	//	m_bStop[0] = true;

	//if (m_tInfo.fY <(m_fY - m_fSpeed) || m_tInfo.fY >(m_fY + m_fSpeed))
	//	m_tInfo.fY -= cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	//else
	//	m_bStop[1] = true;

	//if (m_bStop[0] && m_bStop[1])
	//	m_bRealDead = true;
	
}

void CMonsterBubble::Change_State()
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
			m_tFrame.iEndX = 4;
			m_tFrame.dwDelayTime = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
	}
}

void CMonsterBubble::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelayTime < GetTickCount())
	{
		++m_tFrame.iStartX;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
		{
			m_tFrame.iStartX = 0;
		}
	}
}
