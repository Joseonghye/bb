#pragma once
#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct tagInfo
{
	int iCX;
	int iCY;
	float fX;
	float fY;
	int life;
}INFO;

typedef struct tagLine
{
	tagLine() { ZeroMemory(this, sizeof(LINE)); }
	tagLine(POINT _ptL, POINT _ptR) :ptLeft(_ptL), ptRight(_ptR) {}

	POINT ptLeft;
	POINT ptRight;
}LINE;

#include <wtypes.h>
typedef struct tagFrame
{
	int iStartX;
	int iStartY;
	int iEndX;

	DWORD	dwTime;
	DWORD	dwDelayTime;
}FRAME;

#endif // !__STRUCT_H__
