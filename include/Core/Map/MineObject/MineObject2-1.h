#ifndef __MINEOBJECT21_H__
#define __MINEOBJECT21_H__

#include "Core/Map/MineObject/MineObjectBase.h"

namespace MineObject {

class MineObject21 : public MineObjectBase {

    Q_OBJECT;

public:
    MineObject21(CoreAdapter *_adapter);
    std::string getSymbStr();
    std::string getTypeStr();
};

} // namespace MineObject
#endif
