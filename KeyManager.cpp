#include "stdafx.h"
#include "KeyManager.h"

CKeyManager* CKeyManager::m_pInstance = nullptr;
CKeyManager::CKeyManager()
{
}
CKeyManager::~CKeyManager()
{
}

bool CKeyManager::Key_Pressing(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000)
		return true;
	return false;
}

bool CKeyManager::Key_Down(int _key)
{
	return false;
}

bool CKeyManager::Key_Up(int _key)
{
	return false;
}
