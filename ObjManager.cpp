#include "stdafx.h"
#include "ObjManager.h"
#include "Obj.h"
#include "CollisionManager.h"
#include "Blank.h"

CObjManager* CObjManager::m_pInstance = nullptr;

CObjManager::CObjManager():m_iScore(0), m_iLife(2)
{
}
CObjManager::~CObjManager()
{
	Release();
}

void CObjManager::Initialize()
{
	m_iScore = 0;
	m_iLife = 2;
}

void CObjManager::Update()
{
	Update_Score();

	for (int i = 0; i < OBJID::END; ++i)
	{
		auto iter = m_pObjList[i].begin();
		for (; iter != m_pObjList[i].end(); )
		{
			int iEvent = (*iter)->Update();
			if (OBJ::DEAD == iEvent)
			{
				SAFE_DELETE(*iter);
				iter = m_pObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	//양쪽다 죽음
	CCollisionManager::Collision_Sphere(m_pObjList[OBJID::BUBBLE], m_pObjList[OBJID::MONSTER]);

	//후자만 죽음
	CCollisionManager::Collision_Monster(m_pObjList[OBJID::MONSTER], m_pObjList[OBJID::PLAYER]);
	CCollisionManager::Collision_Bubble(m_pObjList[OBJID::PLAYER], m_pObjList[OBJID::BUBBLE]);
	CCollisionManager::Collision_Bubble(m_pObjList[OBJID::PLAYER], m_pObjList[OBJID::BUBBLE_MONSTER]);
	CCollisionManager::Collision_Item(m_pObjList[OBJID::PLAYER], m_pObjList[OBJID::ITEM]);

	//벽충돌
	CCollisionManager::Collision_RectEx(m_pObjList[OBJID::BLANK], m_pObjList[OBJID::PLAYER]);
	CCollisionManager::Collision_RectEx(m_pObjList[OBJID::BLANK], m_pObjList[OBJID::MONSTER]);
	CCollisionManager::Collision_BubbleEx(m_pObjList[OBJID::BLANK], m_pObjList[OBJID::BUBBLE]);
	CCollisionManager::Collision_BubbleEx(m_pObjList[OBJID::BLANK], m_pObjList[OBJID::BUBBLE_MONSTER]);

	//버블끼리 충돌
	//CCollisionManager::Collision_BubbleBubble(m_pObjList[OBJID::BUBBLE]);

}

void CObjManager::Late_Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_pObjList[i])
		{
			pObj->Late_Update();
		}
	}
}

void CObjManager::Render(HDC _DC)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_pObjList[i])
		{
 			pObj->Render(_DC);
		}
	}
}

void CObjManager::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_pObjList[i].begin(), m_pObjList[i].end(), Safe_Delete<CObj*>);
		m_pObjList[i].clear();
	}
}

void CObjManager::Add_Obj(CObj * pObj, OBJID::ID _id)
{
	m_pObjList[_id].emplace_back(pObj);
}

void CObjManager::Save_BLANK()
{
	HANDLE hFile = CreateFile(L"../Data/Blank3.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"저장 실패!", L"실패", MB_OK);
		return;
	}

	DWORD	dwByte = 0;

	for (auto& pBlank : m_pObjList[OBJID::BLANK])
	{
		WriteFile(hFile, &pBlank->Get_Info(), sizeof(INFO), &dwByte, NULL);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"BLANK 저장 성공!", L"성공", MB_OK);
}

void CObjManager::Load_BLANK()
{
	HANDLE hFile = CreateFile(L"../Data/Blank.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"불러오기 실패!", L"실패", MB_OK);
		return;
	}

	DWORD	dwByte = 0;
	INFO	tTemp = {};

	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_pObjList[OBJID::BLANK].emplace_back(CAbstractFactory<CBlank>::Create(tTemp.fX, tTemp.fY));
	}

	CloseHandle(hFile);
//	MessageBox(g_hWnd, L"BLANK 불러오기 성공!", L"성공", MB_OK);
	//-------------------------------------------
	hFile = CreateFile(L"../Data/Blank2.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"불러오기 실패!", L"실패", MB_OK);
		return;
	}

	float scroll = TILECY*TILEY;
	dwByte = 0;
	tTemp = {};

	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_pObjList[OBJID::BLANK].emplace_back(CAbstractFactory<CBlank>::Create(tTemp.fX, tTemp.fY+ scroll));
	}

	CloseHandle(hFile);
//	MessageBox(g_hWnd, L"BLANK2 불러오기 성공!", L"성공", MB_OK);

	//-----------------------------------------------------------------
	hFile = CreateFile(L"../Data/Blank3.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"불러오기 실패!", L"실패", MB_OK);
		return;
	}

	 scroll = (TILECY*TILEY)*2;
	dwByte = 0;
	tTemp = {};

	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_pObjList[OBJID::BLANK].emplace_back(CAbstractFactory<CBlank>::Create(tTemp.fX, tTemp.fY + scroll));
	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"BLANK2 불러오기 성공!", L"성공", MB_OK);


}

void CObjManager::Set_Stage()
{
	float y = TILECY*TILEY;

	list<CObj*>::iterator iter = m_pObjList[OBJID::BLANK].begin();
	for (; iter != m_pObjList[OBJID::BLANK].end();)
	{
		if ((*iter)->Get_Info().fY < y)
		{
			iter = m_pObjList[OBJID::BLANK].erase(iter);
		}
		else
		{
			(*iter)->Get_Info().fY -= y;
		//	(*iter)->Get_Line().ptRight.y -= y;
			iter++;
		}

	}
}

void CObjManager::Render_ID(HDC _DC,OBJID::ID _id)
{
	for (auto& pObj : m_pObjList[_id])
	{
		pObj->Render(_DC);
	}

}

void CObjManager::Update_Score()
{
	int pos = 10000;
	int val = m_iScore ;

	list<CObj*>::iterator iter = m_pObjList[OBJID::UI].begin();
	for (int i = 0; i < 5; i++)
	{
		int id = (int)(val / pos);
		val = (int)(m_iScore % pos);
		(*iter)->Set_DrawID(id);

		pos /= 10;
		iter++;
	}

}
