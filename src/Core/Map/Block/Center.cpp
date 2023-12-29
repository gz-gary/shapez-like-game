#include "Core/Map/Block/Center.h"
using namespace Block;

Block::Center::Center(int _x, int _y, CoreAdapter* _adapter) :
    DeviceBase(_x, _y, _adapter)
{ }
Block::Center::~Center()
{ }

std::string Block::Center::getSymbStr() const
{
    return "Center";
}
void Block::Center::append(MineObject::MineObjectBase *obj) {
    Block::DeviceBase::append(obj);
    obj->pos = 100;
}

void Block::Center::handleObj(int tick)
{
    for (auto obj : obj_lis)
    {
        if (qcast(obj, MineObject::MineObject1*))
            adapter->Center_changeObjCnt(1, 1);
        else if (qcast(obj, MineObject::MineObject2*))
            adapter->Center_changeObjCnt(2, 1);
        else if (qcast(obj, MineObject::MineObject21*))
            adapter->Center_changeObjCnt(21, 1);
        else if (qcast(obj, MineObject::MineObject22*)) {
            if (obj->angle == 90) adapter->Center_changeObjCnt(221, 1);
            else adapter->Center_changeObjCnt(22, 1);
        }
        delete obj;
    }
    obj_lis.clear();
}

void Block::Center::upgrade() {
    ++grade;
}
