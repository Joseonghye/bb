#include "stdafx.h"
#include "MyEdit.h"
#include "BmpManager.h"
#include "TileManager.h"
#include "LineManager.h"
#include "ObjManager.h"

CMyEdit::CMyEdit() :m_bChcek(true), m_bBlank(false)
{
}

CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize()
{
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Tile/Tile.bmp", L"Tile");
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Tile/Tile2.bmp", L"Tile2");
	CTileManager::Get_Instance()->Initialize();
	num = 0;
}

void CMyEdit::Update()
{
	if (m_bChcek)
	{
		if (GetAsyncKeyState('Q') & 0x8000)
			m_bChcek = false;

		if (!m_bBlank) 
		{
			if (GetAsyncKeyState('W') & 0x8000)
				m_bBlank = true;

			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				CTileManager::Get_Instance()->Picking_Tile(num);
			}
			if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) 
			{

				CTileManager::Get_Instance()->Picking_Tile(num);
			}

			if (GetAsyncKeyState('0') & 0x8000)
				num = 0;
			if (GetAsyncKeyState('1') & 0x8000)
				num = 1;
			if (GetAsyncKeyState('2') & 0x8000)
				num = 2;
			if (GetAsyncKeyState('3') & 0x8000)
				num =3;


			if (GetAsyncKeyState('A') & 0x8000)
				CTileManager::Get_Instance()->Save_Tile();
			if (GetAsyncKeyState('S') & 0x8000)
				CTileManager::Get_Instance()->Load_Tile();
		}
		else
		{
			if (GetAsyncKeyState('W') & 0x8000)
				m_bBlank = false;
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
				CTileManager::Get_Instance()->Add_Rect();

			if (GetAsyncKeyState('A') & 0x8000)
				CObjManager::Get_Instance()->Save_BLANK();
		}
	}
	else {
		if (GetAsyncKeyState('Q') & 0x8000)
			m_bChcek = true;

		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			CLineManager::Get_Instance()->Draw_Line();

		if (GetAsyncKeyState('A') & 0x8000)
			CLineManager::Get_Instance()->Save_Line();
		if (GetAsyncKeyState('S') & 0x8000)
			CLineManager::Get_Instance()->Load_Line();

		if (GetAsyncKeyState(VK_BACK) & 0x8000)
			CLineManager::Get_Instance()->Release();
	}
}

void CMyEdit::Late_Update()
{
}

void CMyEdit::Render(HDC _DC)
{
	CTileManager::Get_Instance()->Render(_DC);
	CLineManager::Get_Instance()->Render(_DC);
	CObjManager::Get_Instance()->Render(_DC);
}

void CMyEdit::Release()
{

}
