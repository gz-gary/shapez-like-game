#include "Core/Map/Block/BlockBase.h"
using namespace Block;

Block::BlockBase::BlockBase(int _x, int _y, CoreAdapter* _adapter) :
    CoreComponent(_adapter),
    x(_x),
    y(_y)
{
}

Block::BlockBase::~BlockBase()
{
}
