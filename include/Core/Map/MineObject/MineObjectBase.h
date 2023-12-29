#ifndef __MINEOBJECT_BASE_H__
#define __MINEOBJECT_BASE_H__

#include "common.h"
#include "Core/CoreComponent.h"

namespace MineObject {

class MineObjectBase : public CoreComponent {

    Q_OBJECT;

public:
    int pos;
    int id;
    int angle;
    int dirty;
    int origin_angle;

public:
    MineObjectBase(CoreAdapter *_adapter);
    virtual ~MineObjectBase();
    virtual std::string getSymbStr() = 0;
    virtual std::string getTypeStr() = 0;


};

extern int total_cnt;

} // namespace MineObject

#endif
