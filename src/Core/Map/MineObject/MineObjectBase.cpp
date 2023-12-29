#include "Core/Map/MineObject/MineObjectBase.h"

int MineObject::total_cnt = 0;

MineObject::MineObjectBase::MineObjectBase(CoreAdapter *_adapter):
    CoreComponent(_adapter),
    pos(0),
    id(++MineObject::total_cnt),
    angle(0),
    dirty(0)
{ }

MineObject::MineObjectBase::~MineObjectBase()
{
    adapter->Device_removeMineObj(id);
}

