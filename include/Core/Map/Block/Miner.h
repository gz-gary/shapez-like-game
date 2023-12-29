#ifndef __MINER_H__
#define __MINER_H__

#include "Core/Map/Block/DeviceBase.h"
#include "Core/Map/Block/Mine.h"

namespace Block {

class Miner : public DirectedDeviceBase {

    Q_OBJECT;

private:
    MineBase *src;
    static int glb_grade;

public:
    Miner(int _x, int _y, Direction _dir_to, CoreAdapter *_adapter);
    ~Miner();
    std::string getSymbStr() const;
    void handleObj(int tick);
    void upgrade();
    void rotate();

    friend class ::Map;
};

} // namespace Block

#endif
