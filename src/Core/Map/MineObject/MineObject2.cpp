#include "Core/Map/MineObject/MineObject2.h"

MineObject::MineObject2::MineObject2(CoreAdapter *_adapter):
    MineObjectBase(_adapter)
{ }


std::string MineObject::MineObject2::getSymbStr()
{
    return "o";
}

std::string MineObject::MineObject2::getTypeStr()
{
    return "2";
}
