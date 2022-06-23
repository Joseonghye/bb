#include "stdafx.h"
#include "Ending.h"
#include "Obj.h"
#include "Number.h"
#include "ObjManager.h"
#include "SceneManager.h"

CEnding::CEnding()
{
}


CEnding::~CEnding()
{
}

void CEnding::Initialize()
{
	CObj* pObj = CAbstractFactory<CNumber>::Create(190, 200);
	pObj->Set_DrawID(0);
	CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::UI);

	pObj = CAbstractFactory<CNumber>::Create(220, 200);
	pObj->Set_DrawID(0);
	CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::UI);

	pObj = CAbstractFactory<CNumber>::Create(250, 200);
	pObj->Set_DrawID(0);
	CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::UI);

	pObj = CAbstractFactory<CNumber>::Create(280, 200);
	pObj->Set_DrawID(0);
	CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::UI);

	pObj = CAbstractFactory<CNumber>::Create(310, 200);
	pObj->Set_DrawID(0);
	CObjManager::Get_Instance()->Add_Obj(pObj, OBJID::UI);
}

void CEnding::Update()
{
	CObjManager::Get_Instance()->Update();
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		CSceneManager::Get_Instance()->Change_Scene(SCENE::LOGO);
}

void CEnding::Late_Update()
{
}

void CEnding::Render(HDC _DC)
{
	CObjManager::Get_Instance()->Render(_DC);
}

void CEnding::Release()
{
}
