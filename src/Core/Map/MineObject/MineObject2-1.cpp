#include "Core/Map/MineObject/MineObject2-1.h"

MineObject::MineObject21::MineObject21(CoreAdapter *_adapter):
    MineObjectBase(_adapter)
{ }

std::string MineObject::MineObject21::getSymbStr()
{
    return "+";
}

std::string MineObject::MineObject21::getTypeStr()
{
    return "21";
}
