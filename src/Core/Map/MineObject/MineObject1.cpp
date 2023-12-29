#include "Core/Map/MineObject/MineObject1.h"

MineObject::MineObject1::MineObject1(CoreAdapter *_adapter):
    MineObjectBase(_adapter)
{ }

std::string MineObject::MineObject1::getSymbStr()
{
    return "*";
}

std::string MineObject::MineObject1::getTypeStr()
{
    return "1";
}
