#pragma once
#ifndef __ENUM_H__
#define __ENUM_H__

namespace OBJID 
{
	enum ID { PLAYER, MONSTER, BUBBLE, BUBBLE_MONSTER,ITEM,BLANK,UI, END };
}
namespace RENDER
{
	enum ID { BACKGROUND, OBJECT, EFFECT, UI, END };
}
namespace OBJ
{
	enum STATE{NOEVENT,DEAD,END};
}
namespace SCENE {
	enum ID{LOGO,STAGE,ENDING,EDIT,END};
}
namespace DIRECT {
	enum DIR {LEFT,RIGHT};
}

namespace MONSTER {
	enum TYPE{ZENCHAN,MIGHTA,END};
}
#endif // !__ENUM_H__
