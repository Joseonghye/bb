#include "stdafx.h"
#include "TileManager.h"
#include "Tile.h"
#include "ObjManager.h"
#include "Blank.h"

CTileManager* CTileManager::m_pInstance = nullptr;
CTileManager::CTileManager()
{
}
CTileManager::~CTileManager()
{
	Release();
}

void CTileManager::Initialize()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float fX = (float)(j * TILECX + (TILECX /2));
			float fY = (float)(i * TILECY + (TILECY /2));

			m_vecTile.emplace_back(CAbstractFactory<CTile>::Create(fX, fY));
		}
	}
}

void CTileManager::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}

void CTileManager::Render(HDC _DC)
{
	for (int i = 0; i < (TILEY*3); ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			int num = (i*TILEX) + j;
			m_vecTile[num]->Render(_DC);
		}
	}

	//for (int i = 0; i < (TILEY ); ++i)
	//{
	//	for (int j = 0; j < TILEX; ++j)
	//	{
	//		int num = (i*TILEX) + j;
	//		m_vecTile[num]->Render(_DC);
	//	}
	//}
}

void CTileManager::Picking_Tile(int _iDrawID)
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	int		x = pt.x / TILECX;
	int		y = pt.y / TILECY;

	int		iIdx = y * TILEX + x;

	if (0 > iIdx || m_vecTile.size() <= (size_t)iIdx)
		return;

	m_vecTile[iIdx]->Set_DrawID(_iDrawID);
}

void CTileManager::Add_Rect()
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	int		x = pt.x / TILECX;
	int		y = pt.y / TILECY;

	int		iIdx = y * TILEX + x;

	if (0 > iIdx || m_vecTile.size() <= (size_t)iIdx)
		return;

	//m_vecTile[iIdx]->Set_DrawID(_iDrawID);

	CObj* pObj = CAbstractFactory<CBlank>::Create(m_vecTile[iIdx]->Get_Info().fX, m_vecTile[iIdx]->Get_Info().fY);
	CObjManager::Get_Instance()->Add_Obj(pObj,OBJID::BLANK);
}


void CTileManager::Save_Tile()
{

	HANDLE hFile = CreateFile(L"../Data/Tile.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"저장 실패!", L"실패", MB_OK);
		return;
	}

	DWORD	dwByte = 0;

	for (auto& pTile : m_vecTile)
	{
		WriteFile(hFile, &pTile->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &pTile->Get_DrawID(), sizeof(int), &dwByte, NULL);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"저장 성공!", L"성공", MB_OK);
}

void CTileManager::Load_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/Tile.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"불러오기 실패!", L"실패", MB_OK);
		return;
	}

	Release();
	DWORD	dwByte = 0;
	INFO	tTemp = {};
	int		iDrawID = 0;

	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_vecTile.emplace_back(CAbstractFactory<CTile>::Create(tTemp.fX, tTemp.fY));
		m_vecTile.back()->Set_DrawID(iDrawID);
	}

	CloseHandle(hFile);
//	MessageBox(g_hWnd, L"Tile 불러오기 성공!", L"성공", MB_OK);

	//------------------------------------------------------
	hFile = CreateFile(L"../Data/Tile2.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"불러오기 실패!", L"실패", MB_OK);
		return;
	}

	dwByte = 0;
	tTemp = {};
	iDrawID = 0;

	float scroll = TILECY*TILEY;
	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_vecTile.emplace_back(CAbstractFactory<CTile>::Create(tTemp.fX, tTemp.fY + scroll));
		m_vecTile.back()->Set_DrawID(iDrawID);
	}

	CloseHandle(hFile);
//	MessageBox(g_hWnd, L"Tile2 불러오기 성공!", L"성공", MB_OK);
	//-----------------------------------------------------------------
	hFile = CreateFile(L"../Data/Tile3.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"불러오기 실패!", L"실패", MB_OK);
		return;
	}

	dwByte = 0;
	tTemp = {};
	iDrawID = 0;

	scroll = (TILECY*TILEY) * 2;
	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_vecTile.emplace_back(CAbstractFactory<CTile>::Create(tTemp.fX, tTemp.fY + scroll));
		m_vecTile.back()->Set_DrawID(iDrawID);
	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"Tile2 불러오기 성공!", L"성공", MB_OK);
}
