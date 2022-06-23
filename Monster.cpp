#include "stdafx.h"
#include "Monster.h"
#include "BmpManager.h"
#include "LineManager.h"
#include "Item.h"
#include "ObjManager.h"
#include "MonsterBubble.h"

CMonster::CMonster()
	:m_eCurState(END), m_ePreState(END), m_bAround(false), m_dwJump(0),
	m_bJump(false), m_fJumpPower(0.f), m_fJumpTime(0.f), m_fJumpY(0.f),
	m_dwTime(0), m_fAngry(0.f), m_bTarget(false), m_iDist(0), m_bDown(true)
{
}
CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_eRenderID = RENDER::OBJECT;

	m_tInfo.iCX = 40;
	m_tInfo.iCY = 40;

	m_fSpeed = 3.0f;
	m_eCurState = WALK;

	m_fJumpPower = 15.f;

	m_dwTime = GetTickCount();
	m_fAngry = 30000.f;
	m_eDir = DIRECT::LEFT;

	m_pTarget = CObjManager::Get_Instance()->Get_Player();
}

int CMonster::Update()
{
	if (m_bDead) 
	{
		if (m_tInfo.fX < WINCX / 2)
			m_eDir = DIRECT::LEFT;
		else
			m_eDir = DIRECT::RIGHT;

		CObj* pObj = CAbstractFactory<CMonsterBubble>::Create(m_tInfo.fX, m_tInfo.fY);
		pObj->Set_Dir(m_eDir);
		pObj->Set_DrawID(1);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::BUBBLE_MONSTER);

		return OBJ::DEAD;
	}

	if (m_dwTime + m_fAngry <= GetTickCount())
	{
		m_fSpeed = 6.f;
		m_eCurState = ANGRY;
	}

	Move();
	Jumping();
	Change_State();

	Update_Frame();
	Update_Rect();
	return OBJ::NOEVENT;
}

void CMonster::Late_Update()
{
}

void CMonster::Render(HDC _DC)
{
	HDC hMemDc = CBmpManager::Get_Instance()->Find_Image(L"Monster");

	if (m_eDir == DIRECT::LEFT) 
	{
		GdiTransparentBlt(_DC,
			m_tRect.left, m_tRect.top,
			m_tInfo.iCX, m_tInfo.iCY,
			hMemDc,
			m_tFrame.iStartX * m_tInfo.iCX, m_tFrame.iStartY * m_tInfo.iCY,
			m_tInfo.iCX, m_tInfo.iCY,
			RGB(15, 79, 174));
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
			, RGB(15, 79, 174));
	}
}

void CMonster::Release()
{
}

void CMonster::Move()
{

	if (m_tInfo.fY >= 512)
		m_tInfo.fY = 0.f;
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
		if (abs(x) <= 2)
			m_bTarget = false;
	}
	else {
		// 같은 라인이면 해당 지점까지 직진
		if (m_tInfo.fY == m_pTarget->Get_Info().fY)
		{
			m_fX = m_pTarget->Get_Info().fX;
			float x = m_fX - m_tInfo.fX;

			if (x < 0)
				m_eDir = DIRECT::LEFT;
			else
				m_eDir = DIRECT::RIGHT;

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
		else if (m_bDown&& !m_bAround)
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
}
	/*
	// 시작과 동시에 전진
	if (m_dwTime + 1300 > GetTickCount()) 
	{
		m_tInfo.fX -= m_fSpeed;
	}
	else {
		if (m_bTarget)
		{
			//있을경우 좌표까지 돌진
			float dir = m_fSpeed;

			if (m_eDir == DIRECT::LEFT)
				dir *= -1;

			m_tInfo.fX += dir;

			float x = m_fX - m_tInfo.fX;

			if (abs(x) <= 2)
				m_bTarget = false;
		}
		else
		{
			//좌우 확인
			if (m_pTarget->Get_Info().fY == m_tInfo.fY)
			{
				m_fX = m_pTarget->Get_Info().fX;
				float x = m_fX - m_tInfo.fX;

				if (x < 0)
					m_eDir = DIRECT::LEFT;
				else
					m_eDir = DIRECT::RIGHT;

				m_bTarget = true;
			}
			else
			{
				if (m_bColl) {
					m_bColl = false;
					// 좌우 살피기 
					if (m_eDir == DIRECT::LEFT)
						m_eDir = DIRECT::RIGHT;
					else
						m_eDir = DIRECT::LEFT;
				}

				// 갈지 말지 랜덤으로 정하기
				int random = rand() % 2;

				// 갈거면 전진
				if (random == 0)
				{
					float dir = m_fSpeed;

					if (m_eDir == DIRECT::LEFT)
						dir *= -1;

					m_tInfo.fX += dir;

					m_iDist++;
					if (m_iDist >= 10)
					{
						m_iDist = 0;
						m_bDown = false;
					}
				}
				// 안갈거면 점프 
				else if (!m_bDown)
				{
					m_fJumpY = m_tInfo.fY;
					m_bJump = true;
				}
			}
		}
	}
	*/


void CMonster::Jumping()
{
	float fY = 0.f;
	bool LineCol = CLineManager::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	if (m_bJump)
	{
		m_fJumpTime += 0.2f;
		m_tInfo.fY = m_fJumpY - ((m_fJumpPower * m_fJumpTime) - (0.5f * 9.8f * m_fJumpTime*m_fJumpTime));

		if (LineCol && m_tInfo.fY >= fY - (m_tInfo.iCY / 2))
		{
			m_dwJump = GetTickCount();
			m_bJump = false;
			m_bAround = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = fY - (m_tInfo.iCY / 2);
		}
	}
	else if (LineCol)
	{
		if (fY - (m_tInfo.iCY / 2) > m_tInfo.fY)
		{
			//int val = rand() % 5;
			//if (val < 2) 
			//{
			//}
			m_bJump = false;
			m_bDown = false;

			m_tInfo.fY += (0.3f * 9.8f);

			if (m_tInfo.fY >= fY - (m_tInfo.iCY / 2))
			{
				m_bDown = true;
				m_tInfo.fY = fY - (m_tInfo.iCY / 2);
			}
		}
		else {
			m_bDown = true;
			m_tInfo.fY = fY - (m_tInfo.iCY / 2);
		}
	}
}

void CMonster::Change_State()
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
		case ANGRY:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 4;
			m_tFrame.iStartY = ANGRY;
			m_tFrame.dwDelayTime = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case AROUND:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 2;
			m_tFrame.iStartY = AROUND;
			m_tFrame.dwDelayTime = 150;
			m_tFrame.dwTime = GetTickCount();
			break;
		case ANGRY_AROUND:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 2;
			m_tFrame.iStartY = ANGRY_AROUND;
			m_tFrame.dwDelayTime = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
	}
}

void CMonster::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelayTime < GetTickCount())
	{
		++m_tFrame.iStartX;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
		{
			m_tFrame.iStartX = 0;

			if (m_eCurState == AROUND) 
			{
				m_eCurState = WALK;
				m_bAround = false;
			}
			else if (m_eCurState == ANGRY_AROUND) {
				m_eCurState = ANGRY;
				m_bAround = false;
			}
		}
	}
}
