#include "stdafx.h"
#include "CollisionManager.h"
#include "Obj.h"
#include "Monster.h"
#include "Bubble.h"
#include "ObjManager.h"

CCollisionManager::CCollisionManager()
{
}


CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	RECT rc = {};

	for (auto& pDst : _Dst)
	{
		for (auto& pSrc : _Src)
		{
			if (IntersectRect(&rc, &pDst->Get_Rect(), &pSrc->Get_Rect()))
			{
				pDst->Set_Dead();
				pSrc->Set_Dead();
			}
		}
	}
}

void CCollisionManager::Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& pDst : _Dst)
	{
		if (pDst->Get_Dead())
			continue;
		for (auto& pSrc : _Src)
		{
			if (pSrc->Get_Dead()) 
				continue;
			if (Check_Sphere(pDst, pSrc))
			{
				pDst->Set_Dead();
				pSrc->Set_Dead();
			}
		}
	}
}
void CCollisionManager::Collision_RectEx(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	float	fX = 0.f, fY = 0.f;

	for (auto& pDst : _Dst)
	{
		for (auto& pSrc : _Src)
		{
			if (Check_Rect(pDst, pSrc, &fX, &fY))
			{
				if (fX < fY)		// 좌우
				{
					//오른쪽으로 밀기
					if (pDst->Get_Info().fX < pSrc->Get_Info().fX)
						pSrc->Set_PosX(fX);
					else //왼쪽으로밀기 
						pSrc->Set_PosX(-fX);

					pSrc->Set_Coll();
				}
				/*else				// 상하
				{
					if (pDst->Get_Info().fY < pSrc->Get_Info().fY)
						pSrc->Set_PosY(fY);
					else
						pSrc->Set_PosY(-fY);
				}*/
			}
		}
	}
}
void CCollisionManager::Collision_BubbleEx(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	float	fX = 0.f, fY = 0.f;

	for (auto& pDst : _Dst)
	{
		for (auto& pSrc : _Src)
		{
			if (Check_Rect(pDst, pSrc, &fX, &fY))
			{
				if (fX < fY)		// 좌우
				{
					if (pDst->Get_Info().fX < pSrc->Get_Info().fX) 
						pSrc->Set_PosX(fX);
					else
						pSrc->Set_PosX(-fX);

					static_cast<CBubble*>(pSrc)->Set_bUp(true);
				}
				else 
				{
					if (pDst->Get_Info().fY < pSrc->Get_Info().fY)
					{
						pSrc->Set_PosY(fY);
						static_cast<CBubble*>(pSrc)->Set_bUp(false);
						pSrc->Reverse_Dir();
						static_cast<CBubble*>(pSrc)->Set_bCenter();
					}
				}
			}
		}
	}

}
void CCollisionManager::Collision_Monster(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	if (_Src.empty())
		return;

	CObj* pSrc = _Src.front();
	for (auto& pDst : _Dst)
	{
		if (!pSrc->Get_Super())
		{
			if (Check_Sphere(pDst, pSrc))
			{
				//플레이어만 사망
				pSrc->Set_Dead();
				//생명 -1
				CObjManager::Get_Instance()->Set_Life();
			}
		}
	}
}

void CCollisionManager::Collision_Bubble(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	if (_Dst.empty())
		return;

	CObj* pDst = _Dst.front();
	for (auto& pSrc : _Src)
	{
		if (pSrc->Get_Super() ||pSrc->Get_Dead())
			continue;
		
		if (Check_Sphere(pDst, pSrc))
		{
			pSrc->Set_Dead();
			//점수 + 
			CObjManager::Get_Instance()->Set_Score(pSrc->Get_Score());
		}
	}
}

void CCollisionManager::Collision_Item(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	if (_Dst.empty())
			return;

	CObj* pDst = _Dst.front();
	for (auto& pSrc : _Src)
	{

		if (Check_Sphere(pDst, pSrc))
		{
			//아이템만 사라짐
			pSrc->Set_Dead();
			//점수 + 
			CObjManager::Get_Instance()->Set_Score(pSrc->Get_Score());
		}
	}
}

void CCollisionManager::Collision_BubbleBubble(list<CObj*>& _Dst)
{
	_Dst.sort(CompareX<CObj*>);
	
	if (_Dst.size() >= 2) 
	{
		list<CObj*>::iterator iter = _Dst.begin();
		list<CObj*>::iterator it = _Dst.begin();
		it++;
		for (; it != _Dst.end(); ++it)
		{
			float y = abs((*iter)->Get_Info().fY - (*it)->Get_Info().fY);
			if (y < 40.f)
			{
    				float x = abs((*iter)->Get_Info().fX - (*it)->Get_Info().fX);
				if (x <= 38.f)
				{
					float _x = 38.f - x;
					(*iter)->Set_PosX(-20);
				}
			}
		}
	}
}


bool CCollisionManager::Check_Sphere(CObj* _pDst, CObj* _pSrc)
{
	float fX = abs(_pDst->Get_Info().fX - _pSrc->Get_Info().fX);
	float fY = abs(_pDst->Get_Info().fY - _pSrc->Get_Info().fY);
	float fDia = sqrtf(fX * fX + fY * fY);

	float fSumRad = (float)((_pDst->Get_Info().iCX + _pSrc->Get_Info().iCX) >> 1);

	if (fSumRad >= fDia)
		return true;
	return false;
}

bool CCollisionManager::Check_Rect(CObj * _pDst, CObj * _pSrc, float * _x, float * _y)
{
	float	fSumRadX = (float)((_pDst->Get_Info().iCX + _pSrc->Get_Info().iCX) >> 1);
	float	fSumRadY = (float)((_pDst->Get_Info().iCY + _pSrc->Get_Info().iCY) >> 1);

	float	fDisX = abs(_pDst->Get_Info().fX - _pSrc->Get_Info().fX);
	float	fDisY = abs(_pDst->Get_Info().fY - _pSrc->Get_Info().fY);

	if (fSumRadX > fDisX && fSumRadY > fDisY)
	{
		*_x = fSumRadX - fDisX;
		*_y = fSumRadY - fDisY;
		return true;
	}
	return false;
}
