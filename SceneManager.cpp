#include "stdafx.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Logo.h"
#include "MyEdit.h"
#include "Ending.h"
#include "ObjManager.h"

CSceneManager* CSceneManager::m_pInstance = nullptr;
CSceneManager::CSceneManager() 
	:m_pScene(nullptr), m_eCurScene(SCENE::END)
{
}
CSceneManager::~CSceneManager()
{
}

void CSceneManager::Change_Scene(SCENE::ID _id)
{
	if (m_eCurScene == _id)
		return;
	
	m_eCurScene = _id;
	Release();
	switch (m_eCurScene)
	{
	case SCENE::LOGO:
		m_pScene = new CLogo;
		break;
	case SCENE::STAGE:
		m_pScene = new CStage;
		break;
	case SCENE::ENDING:
		m_pScene = new CEnding;
		CObjManager::Get_Instance()->Release();
		break;
	case SCENE::EDIT:
		m_pScene = new CMyEdit;
		break;
	}
	m_pScene->Initialize();
}

void CSceneManager::Update()
{
	m_pScene->Update();
}

void CSceneManager::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneManager::Render(HDC _DC)
{
	m_pScene->Render(_DC);
}

void CSceneManager::Release()
{
	SAFE_DELETE(m_pScene);
}
