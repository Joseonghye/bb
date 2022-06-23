#pragma once

class CScene;
class CSceneManager
{
private:
	CSceneManager();
	~CSceneManager();

public:
	void Change_Scene(SCENE::ID _id);
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

	static CSceneManager* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneManager;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CSceneManager* m_pInstance;

	CScene* m_pScene;

	SCENE::ID m_eCurScene;
//	SCENE::ID m_ePreScene;
	
};

