#pragma once
class CKeyManager
{
private:
	CKeyManager();
	~CKeyManager();

public:
	static CKeyManager* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CKeyManager;
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

public:
	bool Key_Pressing(int _key);
	bool Key_Down(int _key);
	bool Key_Up(int _key);

private:
	static CKeyManager* m_pInstance;

};

