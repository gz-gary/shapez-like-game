#ifndef __MINEOBJECT1_H__
#define __MINEOBJECT1_H__

#include "Core/Map/MineObject/MineObjectBase.h"

namespace MineObject
{
class MineObject1 : public MineObjectBase
{

    Q_OBJECT;

public:
    MineObject1(CoreAdapter *_adapter);
    std::string getSymbStr();
    std::string getTypeStr();
};

} // namespace MineObject

#endif
