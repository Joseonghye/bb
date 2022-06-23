#include "stdafx.h"
#include "Logo.h"
#include "SceneManager.h"
#include "BmpManager.h"

CLogo::CLogo()
{
}
CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	CBmpManager::Get_Instance()->Insert_Bmp(L"../Image/Title.bmp", L"Title");
}

void CLogo::Update()
{

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ 
		CSceneManager::Get_Instance()->Change_Scene(SCENE::STAGE);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		CSceneManager::Get_Instance()->Change_Scene(SCENE::EDIT);
	}

}

void CLogo::Late_Update()
{
}

void CLogo::Render(HDC _DC)
{
	HDC hMemDc = CBmpManager::Get_Instance()->Find_Image(L"Title");

	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDc, 0, 0, SRCCOPY);
}

void CLogo::Release()
{
}
