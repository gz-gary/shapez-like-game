#include "Core/Map/Block/Empty.h"
using namespace Block;

Block::Empty::Empty(int _x, int _y, CoreAdapter* _adapter) :
    BlockBase(_x, _y, _adapter)
{
}

Block::Empty::~Empty()
{
}

std::string Block::Empty::getSymbStr() const
{
    return "Empty";
}
