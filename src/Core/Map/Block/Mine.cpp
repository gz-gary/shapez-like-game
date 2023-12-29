#include "Core/Map/Block/Mine.h"

using namespace Block;
using namespace MineObject;

Block::MineBase::MineBase(int _x, int _y, CoreAdapter* _adapter, MineType _type) :
    BlockBase(_x, _y, _adapter), type(_type)
{ }

Block::MineBase::~MineBase() { }

MineType Block::MineBase::getType() const {
    return type;
}


Block::Mine1::Mine1(int _x, int _y, CoreAdapter* _adapter) :
    MineBase(_x, _y, _adapter, MineType::Mine1)
{ }

Block::Mine1::~Mine1()
{ }

std::string Block::Mine1::getSymbStr() const
{
    return "Mine1";
}

MineObject::MineObject1* Block::Mine1::produce()
{
    auto tmp = new MineObject1(adapter);
    adapter->All_newMineObj(tmp->id, tmp->getSymbStr());
    return tmp;
}

Block::Mine2::Mine2(int _x, int _y, CoreAdapter* _adapter) :
    MineBase(_x, _y, _adapter, MineType::Mine2)
{ }

Block::Mine2::~Mine2()
{ }

std::string Block::Mine2::getSymbStr() const
{
    return "Mine2";
}

MineObject::MineObject2 *Block::Mine2::produce()
{
    auto tmp = new MineObject2(adapter);
    adapter->All_newMineObj(tmp->id, tmp->getSymbStr());
    return tmp;
}
