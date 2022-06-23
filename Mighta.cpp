#include "stdafx.h"
#include "Mighta.h"
#include "Ball.h"
#include "ObjManager.h"
#include "BmpManager.h"
#include "MonsterBubble.h"

CMighta::CMighta():m_pBall(nullptr)
{
}
CMighta::~CMighta()
{
	Release();
}

void CMighta::Initialize()
{
	m_eRenderID = RENDER::OBJECT;

	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_fSpeed = 4.f;
	m_fJumpPower = 15.f;
	m_eCurState = WALK;

	m_dwTime = GetTickCount();
	m_fAngry = 30000.f;
	m_eDir = DIRECT::LEFT;
	m_pTarget = CObjManager::Get_Instance()->Get_Player();
}

int CMighta::Update()
{

	if (m_tInfo.fY >= 512)
		m_tInfo.fY = 0.f;

	if (m_bDead)
	{
		if (m_tInfo.fX < WINCX / 2)
			m_eDir = DIRECT::LEFT;
		else
			m_eDir = DIRECT::RIGHT;

		CObj* pObj = CAbstractFactory<CMonsterBubble>::Create(m_tInfo.fX, m_tInfo.fY);
		pObj->Set_Dir(m_eDir);
		pObj->Set_DrawID(2);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::BUBBLE_MONSTER);

		return OBJ::DEAD;
	}

	if (m_dwTime + m_fAngry <= GetTickCount())
	{
		m_fSpeed = 7.f;
		m_eCurState = ANGRY;
	}

	Jumping();
	Move();
	Change_State();

	Update_Frame();
	Update_Rect();
	return OBJ::NOEVENT;
}

void CMighta::Render(HDC _DC)
{
	HDC hMemDc = CBmpManager::Get_Instance()->Find_Image(L"Monster_2");

	if (m_eDir == DIRECT::LEFT)
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
		HDC hStretchDC = CBmpManager::Get_Instance()->Find_Image(L"StrechMonster");
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

void CMighta::Move()
{
	if (m_bTarget)
	{
		if (m_bColl)
		{
			m_bColl = false;
			//m_bTarget = false;
			// 좌우 살피기 
			if (m_eDir == DIRECT::LEFT)
				m_eDir = DIRECT::RIGHT;
			else
				m_eDir = DIRECT::LEFT;
		}

		float dir = m_fSpeed;
		if (m_eDir == DIRECT::LEFT)
			dir *= -1;

		m_tInfo.fX += dir;

		float x = m_fX - m_tInfo.fX;

		//가까워지면 멈추기 
		if (abs(x) <= 5)
			m_bTarget = false;
	}
	else {
		// 같은 라인이면 해당 지점까지 직진
		if (m_tInfo.fY == m_pTarget->Get_Info().fY)
		{
			m_fX = m_pTarget->Get_Info().fX;
			float x = m_fX - m_tInfo.fX;
			float dist = 10.f;

			if (x < 0) 
			{
				m_eDir = DIRECT::LEFT;
				dist *= -1;
			}
			else
				m_eDir = DIRECT::RIGHT;

			//돌 만들기 
			if (!m_pBall ||m_pBall->Get_Dead())
			{
				CObj* pObj = CAbstractFactory<CBall>::Create(m_tInfo.fX + dist, m_tInfo.fY);
				pObj->Set_Dir(m_eDir);
				CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);
				m_pBall = pObj;
			}

			m_bTarget = true;
		}
		// 점프
		else if (m_tInfo.fY > m_pTarget->Get_Info().fY)
		{
			//주위 살피고
			if (!m_bAround)
			{
				if (m_eCurState == ANGRY)
					m_eCurState = ANGRY_AROUND;
				else
					m_eCurState = AROUND;
				m_bAround = true;
			}
			//점프
			else if (m_dwJump + 700 < GetTickCount())
			{
				m_fJumpY = m_tInfo.fY;
				m_bJump = true;
			}
			else
			{
				float dir = m_fSpeed;

				if (m_eDir == DIRECT::LEFT)
					dir *= -1;

				m_tInfo.fX += dir;
			}
		}
		//주변안보고 점프안할때 
		else if (m_bDown && !m_bAround)
		{
			//가다가 벽에 박으면 반대로.
			if (m_bColl)
			{
				m_bColl = false;
				// 좌우 살피기 
				if (m_eDir == DIRECT::LEFT)
					m_eDir = DIRECT::RIGHT;
				else
					m_eDir = DIRECT::LEFT;
			}

			float dir = m_fSpeed;

			if (m_eDir == DIRECT::LEFT)
				dir *= -1;

			m_tInfo.fX += dir;

			m_iDist++;
			if (m_iDist >= rand() % 50 + 30)
			{
				m_iDist = 0;
			}
		}
	}
	/*
	if (m_bTarget)
	{
		float dir = m_fSpeed;

		if (m_eDir == DIRECT::LEFT)
			dir *= -1;

		m_tInfo.fX += dir;

		float x = m_fX - m_tInfo.fX;

		if (abs(x) <= 2)
			m_bTarget = false;
	}
	//플레이어가 같은 라인
	else {
		if (m_pTarget->Get_Info().fY == m_tInfo.fY)
		{
			m_fX = m_pTarget->Get_Info().fX;
			float x = m_fX - m_tInfo.fX;
			float dist = 3;

			if (x < 0)
			{
				m_eDir = DIRECT::LEFT;
				dist *= -1;
			}
			else
				m_eDir = DIRECT::RIGHT;

			//돌 만들기 
			if (!m_pBall)
			{
				CObj* pObj = CAbstractFactory<CBall>::Create(m_tInfo.fX + dist, m_tInfo.fY);
				pObj->Set_Dir(m_eDir);
				CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);
				m_pBall = pObj;
			}
			m_bTarget = true;
		}
		else if (m_pTarget->Get_Info().fY < m_tInfo.fY)
		{
			//if (!m_bAround)
			//{
			//if (m_eCurState == ANGRY)
			//m_eCurState = ANGRY_AROUND;
			//else
			//m_eCurState = AROUND;
			//}
			//else 
			if (m_dwJump + 500 < GetTickCount())
			{
				m_fJumpY = m_tInfo.fY;
				m_bJump = true;
			}
		}

		if (!m_bJump) //&& m_bAround)
		{
			//벽에 부딪쳤을때 반대로 
			if (m_bColl)
			{
				m_bColl = false;
				// 좌우 살피기 
				if (m_eDir == DIRECT::LEFT)
					m_eDir = DIRECT::RIGHT;
				else
					m_eDir = DIRECT::LEFT;
			}

			//전진 
			float dir = m_fSpeed;

			if (m_eDir == DIRECT::LEFT)
				dir *= -1;

			m_tInfo.fX += dir;

			m_iDist++;
			if (m_iDist >= 10)
			{
				m_iDist = 0;
			}
		}
	}
	*/
}

void CMighta::Change_State()
{
	if (m_ePreState != m_eCurState)
	{
		m_ePreState = m_eCurState;
		switch (m_eCurState)
		{
		case WALK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 2;
			m_tFrame.iStartY = WALK;
			m_tFrame.dwDelayTime = 150;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ANGRY:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 2;
			m_tFrame.iStartY = ANGRY;
			m_tFrame.dwDelayTime = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
	}
}
