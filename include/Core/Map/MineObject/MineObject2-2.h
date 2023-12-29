#ifndef __MINEOBJECT22_H__
#define __MINEOBJECT22_H__

#include "Core/Map/MineObject/MineObjectBase.h"

namespace MineObject {

class MineObject22 : public MineObjectBase {

    Q_OBJECT;

public:
    MineObject22(CoreAdapter *_adapter);
    std::string getSymbStr();
    std::string getTypeStr();
};

} // namespace MineObject
#endif
