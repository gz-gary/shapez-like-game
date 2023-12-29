#ifndef __TRASHBIN_H__
#define __TRASHBIN_H__

#include "Core/Map/Block/DeviceBase.h"

namespace Block {

class Trashbin : public DeviceBase {

    Q_OBJECT;

public:
    Trashbin(int _x, int _y, CoreAdapter* _adapter);
    ~Trashbin();
    std::string getSymbStr() const;
    void upgrade();
    void handleObj(int tick);
};

} // namespace Block

#endif
