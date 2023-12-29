#include "Core/Map/Block/Trashbin.h"
using namespace Block;

Block::Trashbin::Trashbin(int _x, int _y, CoreAdapter* _adapter) :
    DeviceBase(_x, _y, _adapter)
{
    info.symb_str = "Trashbin";
}

Block::Trashbin::~Trashbin() { }

std::string Block::Trashbin::getSymbStr() const
{
    return info.symb_str;
}

void Block::Trashbin::handleObj(int tick)
{
    for (auto obj : obj_lis)
        delete obj;
    obj_lis.clear();
}

void Block::Trashbin::upgrade() {
    ++grade;
}
