#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"

CLine::CLine()
{
}

CLine::CLine(POINT & _left, POINT & _right)
	:m_tLine(_left, _right)
{
}

CLine::~CLine()
{
	Release();
}

void CLine::Initialize()
{
}

void CLine::Render(HDC _DC)
{
	//float ScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HPEN pen = CreatePen(PS_SOLID,3,RGB(0, 0, 255));
	HPEN oPen = (HPEN)SelectObject(_DC, pen);

	MoveToEx(_DC, (int)m_tLine.ptLeft.x , (int)m_tLine.ptLeft.y, nullptr);
	LineTo(_DC, (int)m_tLine.ptRight.x, (int)m_tLine.ptRight.y);
	
	SelectObject(_DC, oPen);
	DeleteObject(pen);
}

void CLine::Release()
{
}
