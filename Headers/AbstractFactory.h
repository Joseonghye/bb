#pragma once
#ifndef __ABSTRACTFACTORY_H__
#define __ABSTRACTFACTORY_H__
#include "Monster.h"

class CObj;
class CUI;

template <typename T>
class CAbstractFactory
{
public:
	static CObj* Create(float _x, float _y)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);

		return pObj;
	}
	static CObj* Create_AngryMonster (float _x, float _y)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		static_cast<CMonster*>(pObj)->Set_Angry();

		return pObj;
	}

	static CObj* Create_UI(float _x, float _y,int _type)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_x, _y);
		pObj->Set_DrawID(_type);
		pObj->Initialize();
		

		return pObj;
	}

};

#endif // !__ABSTRACTFACTORY_H__
