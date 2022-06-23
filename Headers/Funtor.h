#pragma once
#ifndef __FUNCTOR_H__
#define __FUNCTOR_H__
#include <tchar.h>
#include <windows.h>

class CStrCmp
{
public:
	CStrCmp(const TCHAR* _pString) :m_pString(_pString) {}

public:
	template<typename T>
	bool operator()(T& _Dst)
	{
		return !lstrcmp(m_pString, _Dst.first);
	}


private:
	const TCHAR* m_pString;
};


#endif // !__FUNCTOR_H__
