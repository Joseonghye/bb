#include "stdafx.h"
#include "LineManager.h"
#include "Line.h"

CLineManager* CLineManager::m_pInstance = nullptr;
CLineManager::CLineManager()
	:m_bCheck(true), iY(10000)
{
	ZeroMemory(m_LinePt, sizeof(POINT)*2);
}
CLineManager::~CLineManager()
{
	Release();
}

void CLineManager::Initialize()
{
}

void CLineManager::Render(HDC _DC)
{
	for (auto& pLine : m_pLineList)
		pLine->Render(_DC);
}

void CLineManager::Release()
{
	for_each(m_pLineList.begin(), m_pLineList.end(), Safe_Delete<CLine*>);
	m_pLineList.clear();
}

void CLineManager::Draw_Line()
{
	POINT pt = {};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (m_bCheck)
	{
		if (abs(iY - pt.y)> 5)
			iY = pt.y;
		else
			pt.y = iY;

		m_LinePt[0] = pt;
		m_bCheck = false;
	}
	else
	{
		m_LinePt[1] = pt;
		m_LinePt[1].y = iY;

		m_pLineList.emplace_back(new CLine(m_LinePt[0], m_LinePt[1]));

		m_bCheck = true;
	}
}

void CLineManager::Save_Line()
{
	HANDLE hFile = CreateFile(L"../Data/Line3.dat", GENERIC_WRITE,
		NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"저장실패", L"실패", MB_OK);
		return;
	}
	DWORD dwByte = 0;
	for (auto& pLine : m_pLineList)
		WriteFile(hFile, &pLine->Get_Line(), sizeof(LINE), &dwByte, NULL);

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"저장 성공", L"성공", MB_OK);
}

void CLineManager::Load_Line()
{
	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_READ,
		NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"불러오기 실패", L"실패", MB_OK);
		return;
	}

	Release();

	LINE tTemp;
	DWORD dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(LINE), &dwByte, NULL);

		if (dwByte == 0)
			break;
		
		m_pLineList.emplace_back(new CLine(tTemp.ptLeft, tTemp.ptRight));
	}

	CloseHandle(hFile);
//	MessageBox(g_hWnd, L"Line 불러오기 성공", L"성공", MB_OK);
//---------------------------------------------

	hFile = CreateFile(L"../Data/Line2.dat", GENERIC_READ,
		NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"불러오기 실패", L"실패", MB_OK);
		return;
	}

	//Release();
	float scroll = TILECY*TILEY;
	 tTemp;
	 dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(LINE), &dwByte, NULL);

		if (dwByte == 0)
			break;

		tTemp.ptLeft.y += scroll;
		tTemp.ptRight.y += scroll;
		m_pLineList.emplace_back(new CLine(tTemp.ptLeft, tTemp.ptRight));
	}

	CloseHandle(hFile);
//	MessageBox(g_hWnd, L"Line2 불러오기 성공", L"성공", MB_OK);
//-------------------------------------------------------
	hFile = CreateFile(L"../Data/Line3.dat", GENERIC_READ,
		NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, L"불러오기 실패", L"실패", MB_OK);
		return;
	}

	//Release();
	scroll = (TILECY*TILEY)*2;
	tTemp;
	dwByte = 0;

	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(LINE), &dwByte, NULL);

		if (dwByte == 0)
			break;

		tTemp.ptLeft.y += scroll;
		tTemp.ptRight.y += scroll;
		m_pLineList.emplace_back(new CLine(tTemp.ptLeft, tTemp.ptRight));
	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"Line2 불러오기 성공", L"성공", MB_OK);


}

void CLineManager::Set_Stage()
{
	float y = TILECY*TILEY;

	list<CLine*>::iterator iter = m_pLineList.begin();
	for(;iter!= m_pLineList.end();)
	{
		if ((*iter)->Get_Line().ptLeft.y < y)
		{
			iter = m_pLineList.erase(iter);
		}
		else
		{
			(*iter)->Get_Line().ptLeft.y -= y;
			(*iter)->Get_Line().ptRight.y -= y;
			iter++;
		}

	}
}

bool CLineManager::Collision_Line(float _x, float _y, float* _fY)
{
	if (m_pLineList.empty())
		return false;

	float dist = 1000.f;
	float y = 0;

	for (auto& pLine : m_pLineList)
	{
		if (pLine->Get_Line().ptLeft.x <= _x &&
			pLine->Get_Line().ptRight.x > _x)
		{
			float	x1 = (float)pLine->Get_Line().ptLeft.x;
			float	y1 = (float)pLine->Get_Line().ptLeft.y;
			float	x2 = (float)pLine->Get_Line().ptRight.x;
			float	y2 = (float)pLine->Get_Line().ptRight.y;

			float fY = y1 - _y;
			float d = sqrtf( fY* fY );
			if (d < dist)
			{
				if (_y < y1) {
					dist = d;
					y = y1;
				}
			}

		//	*_fY = ((y2 - y1) / (x2 - x1)) * (_x - x1) + y1;
		}	
	}
	if (y != 0)
	{
		*_fY = y;
		return true;
	}

	return false;
}
