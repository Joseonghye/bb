#pragma once
#ifndef __FUNCTION_H__
#define __FUNCTION_H__

template <typename T>
void Safe_Delete(T& _Dst)
{
	if (_Dst)
	{
		delete _Dst;
		_Dst = nullptr;
	}
}

template <typename T>
bool CompareX(T& _Dst, T& _Src)
{
	return _Dst->Get_Info().fX  < _Src->Get_Info().fX;
}

#endif // !__FUNCTION_H__
