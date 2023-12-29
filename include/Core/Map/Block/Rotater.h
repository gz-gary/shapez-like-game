#ifndef __ROTATER_H__
#define __ROTATER_H__

#include "Core/Map/Block/DeviceBase.h"

namespace Block
{

class Rotater : public DirectedDeviceBase
{

    Q_OBJECT;

    friend class ::Map;

private:
    int alt;
    static int glb_grade;

public:
    Rotater(int _x, int _y, Direction _dir_to, int _alt, CoreAdapter *_adapter);
    ~Rotater();
    std::string getSymbStr() const;
    void upgrade();
    void handleObj(int tick);
    void rotate();
};

} // namespace Block

#endif
