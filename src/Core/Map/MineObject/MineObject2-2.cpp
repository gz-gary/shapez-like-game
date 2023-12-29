#include "Core/Map/MineObject/MineObject2-2.h"

MineObject::MineObject22::MineObject22(CoreAdapter *_adapter):
    MineObjectBase(_adapter)
{ }


std::string MineObject::MineObject22::getSymbStr()
{
    return "-";
}

std::string MineObject::MineObject22::getTypeStr()
{
    return "22";
}
