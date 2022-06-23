#include "stdafx.h"
#include "MainGame.h"
#include "BmpManager.h"
#include "SceneManager.h"
#include "LineManager.h"
#include "ObjManager.h"
#include "TileManager.h"

CMainGame::CMainGame()
{
}
CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Back2.bmp", L"BackBuffer");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Tile/Tile.bmp", L"Tile");
	CSceneManager::Get_Instance()->Change_Scene(SCENE::LOGO);
//	CSceneManager::Get_Instance()->Change_Scene(SCENE::STAGE);
}

void CMainGame::Update()
{
	CSceneManager::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneManager::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	HDC hMemDC = CBmpManager::Get_Instance()->Find_Image(L"Back");
	HDC hBackDC = CBmpManager::Get_Instance()->Find_Image(L"BackBuffer");

	BitBlt(hMemDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);

	CSceneManager::Get_Instance()->Render(hMemDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

#ifdef _DEBUG
	++m_iFPS;
	if (m_dwFPSTime + 1000 < GetTickCount())
	{
		TCHAR	szFPS[16] = L"";
		swprintf_s(szFPS, L"FPS: %d", m_iFPS);
		SetWindowText(g_hWnd, szFPS);

		m_iFPS = 0;
		m_dwFPSTime = GetTickCount();
	}
#endif
}

void CMainGame::Release()
{
	CSceneManager::Get_Instance()->Destroy_Instance();
	CBmpManager::Get_Instance()->Destroy_Instance();
	CLineManager::Get_Instance()->Destroy_Instance();
	CObjManager::Get_Instance()->Destroy_Instance();
	CTileManager::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}
