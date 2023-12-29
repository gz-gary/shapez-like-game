#ifndef __CUTTER_H__
#define __CUTTER_H__

#include "Core/Map/Block/DeviceBase.h"

namespace Block
{

class Cutter : public DirectedDeviceBase
{

    Q_OBJECT;

    friend class ::Map;

private:
    int alt;
    Cutter *couple;
    static int glb_grade;
    bool obj_cut;

public:
    Cutter(int _x, int _y, Direction _dir_frm, Direction _dir_to, int _alt, CoreAdapter *_adapter);
    ~Cutter();
    std::string getSymbStr() const;
    void upgrade();
    void resetDelivery();
    void handleObj(int tick);
    void rotate();
};

} // namespace Block

#endif
