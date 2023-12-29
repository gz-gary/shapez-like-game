#ifndef __MINEOBJECT2_H__
#define __MINEOBJECT2_H__

#include "Core/Map/MineObject/MineObjectBase.h"

namespace MineObject {

class MineObject2 : public MineObjectBase {

    Q_OBJECT;

public:
    MineObject2(CoreAdapter *_adapter);
    std::string getSymbStr();
    std::string getTypeStr();
};

} // namespace MineObject
#endif
