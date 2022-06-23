#include "stdafx.h"
#include "Stage.h"
#include "Player.h"
#include "Monster.h"
#include "ObjManager.h"
#include "BmpManager.h"
#include "TileManager.h"
#include "LineManager.h"
#include "Mighta.h"
#include "Number.h"
#include "ScrollMgr.h"
#include "SceneManager.h"

CStage::CStage() :m_bNext(false), m_fY(0), m_iStage(0)
{
}
CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	//플레이어 
	if (m_iStage == 0) 
	{
		CObjManager::Get_Instance()->Initialize();

		CObj* pObj = CAbstractFactory<CPlayer>::Create(70, 394);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::PLAYER);

		//몬스터
	//	pObj = CAbstractFactory<CMighta>::Create(250, 150);
	//	CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);
		pObj = CAbstractFactory<CMonster>::Create(250, 150);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);
		pObj = CAbstractFactory<CMonster>::Create(250, 130);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);
		pObj = CAbstractFactory<CMonster>::Create(250, 160);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);

		//점수 
		pObj = CAbstractFactory<CNumber>::Create(20, 30);
		pObj->Set_DrawID(0);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::UI);

		pObj = CAbstractFactory<CNumber>::Create(50, 30);
		pObj->Set_DrawID(0);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::UI);

		pObj = CAbstractFactory<CNumber>::Create(80, 30);
		pObj->Set_DrawID(0);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::UI);

		pObj = CAbstractFactory<CNumber>::Create(110, 30);
		pObj->Set_DrawID(0);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::UI);

		pObj = CAbstractFactory<CNumber>::Create(140, 30);
		pObj->Set_DrawID(0);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::UI);

		CTileManager::Get_Instance()->Load_Tile();
		CLineManager::Get_Instance()->Load_Line();
		CObjManager::Get_Instance()->Load_BLANK();

		CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Tile/Tile.bmp", L"Tile");
		CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Tile/Tile.bmp", L"Tile2");

		CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster.bmp", L"Monster");
		CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/StrechMonster.bmp", L"StrechMonster");
		CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster_2.bmp", L"Monster_2");
		CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Monster/Ball.bmp", L"Ball");

		CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Item/banana.bmp", L"Item_banana");
		CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/UI/Score_1000.bmp", L"Score_1000");
		CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/UI/Number.bmp", L"Number");
	}
	else if (m_iStage == 1)
	{
		CLineManager::Get_Instance()->Set_Stage();
		CObjManager::Get_Instance()->Set_Stage();

		//float ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
		CObj* pObj = CAbstractFactory<CPlayer>::Create(70.f, 394.f);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::PLAYER);

		pObj = CAbstractFactory<CMonster>::Create(100, 210.f );
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);
		pObj = CAbstractFactory<CMonster>::Create(300, 130.f );
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);
		pObj = CAbstractFactory<CMonster>::Create(250.f, 300.f);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);
	}
	else if (m_iStage == 2)
	{
		CLineManager::Get_Instance()->Set_Stage();
		CObjManager::Get_Instance()->Set_Stage();

		CObj* pObj = CAbstractFactory<CPlayer>::Create(70.f, 394.f);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::PLAYER);

		pObj = CAbstractFactory<CMighta>::Create(300, 200);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);
		pObj = CAbstractFactory<CMighta>::Create(150, 250);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);

		pObj = CAbstractFactory<CMonster>::Create(400, 250);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);
		pObj = CAbstractFactory<CMonster>::Create(300, 150);
		CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::MONSTER);
	}
	else
	{
		CSceneManager::Get_Instance()->Change_Scene(SCENE::ENDING);
	}

	
}

void CStage::Update()
{
	if (CObjManager::Get_Instance()->Get_Life() <= 0)
	{
		CSceneManager::Get_Instance()->Change_Scene(SCENE::ENDING);
	}

	if (CObjManager::Get_Instance()->Get_Next()) 
	{
		if (!m_bNext)
		{
			m_dwTime = GetTickCount();
			m_bNext = true;
		}
		else if(m_dwTime + 12000 < GetTickCount())
		{
			CObjManager::Get_Instance()->Delete_Player();
			m_fY += 3.f;
			CScrollMgr::Get_Instance()->Set_ScrollY(-3.f);
			if (m_fY >= WINCY - 45.f) 
			{
				m_bNext = false;
				m_fY = 0.f;

				m_iStage++;
				Initialize();
			 }
		}
	}
		CObjManager::Get_Instance()->Update();

//	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
//		m_bNext = true;
}

void CStage::Late_Update()
{
	CObjManager::Get_Instance()->Late_Update();
}

void CStage::Render(HDC _DC)
{
	CTileManager::Get_Instance()->Render(_DC);
//	CLineManager::Get_Instance()->Render(_DC);
	CObjManager::Get_Instance()->Render(_DC);
}

void CStage::Release()
{
}
