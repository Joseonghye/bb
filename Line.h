#pragma once
#ifndef __LINE_H__
#define __LINE_H__

class CLine
{
public:
	CLine();
	CLine(POINT& _left, POINT& _right);
	~CLine();

public:
	void Initialize();
	void Render(HDC _DC);
	void Release();

	 LINE& Get_Line() { return m_tLine; }

private:
	LINE m_tLine;
};

#endif // !__LINE_H__
