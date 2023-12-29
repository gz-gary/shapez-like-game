#ifndef __CENTER_H__
#define __CENTER_H__

#include "Core/Map/Block/DeviceBase.h"

namespace Block
{

class Center : public DeviceBase {

    Q_OBJECT;

public:
    Center(int _x, int _y, CoreAdapter* _adapter);
    ~Center();
    std::string getSymbStr() const;
    void upgrade();
    void handleObj(int tick);
    virtual void append(MineObject::MineObjectBase *obj);

};

} // namespace Block

#endif
