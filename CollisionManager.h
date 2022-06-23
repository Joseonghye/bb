#pragma once
class CCollisionManager
{
public:
	CCollisionManager();
	~CCollisionManager();

	static void Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src);

	static void Collision_RectEx(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_BubbleEx(list<CObj*>& _Dst, list<CObj*>& _Src);
	
	static void Collision_Monster(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Bubble(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Item(list<CObj*>& _Dst, list<CObj*>& _Src);

	static void Collision_BubbleBubble(list<CObj*>& _Dst);
private:
	static bool Check_Sphere(CObj* _pDst, CObj* _pSrc);
	static bool Check_Rect(CObj* _pDst, CObj* _pSrc, float* _x, float* _y);

};

