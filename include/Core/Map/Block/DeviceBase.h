#ifndef __DEVICE_BASE_H__
#define __DEVICE_BASE_H__

#include "Core/CoreAdapter.h"
#include "Core/Map/Block/BlockBase.h"
#include "Core/Map/Block/Direction.h"
#include "Core/Map/MineObject/MineObject.h"

namespace Block {

struct DisplayInfo {
    float x0, y0, x1, y1, x2, y2;
    std::string symb_str;
    int flag;
    int dir;
    float ori;
};

class DeviceBase : public BlockBase {

    Q_OBJECT;

    friend class ::Map;
    friend class DirectedDeviceBase;

protected:
    std::list<MineObject::MineObjectBase *> obj_lis;
    int grade;
    bool obj_delivered;
    DisplayInfo info;

public:
    DeviceBase(int _x, int _y, CoreAdapter* _adapter);
    virtual void resetDelivery();
    virtual ~DeviceBase();
    virtual void upgrade() = 0;
    virtual void handleObj(int tick) = 0;
    virtual void append(MineObject::MineObjectBase *obj);
    int full();
};

class DirectedDeviceBase : public DeviceBase {

    Q_OBJECT;

    friend bool checkFrmTo(const DirectedDeviceBase *, const BlockBase *);
    friend std::string strDir(Direction dir);
    friend ::Map;
    friend class DeviceBase;

protected:
    Direction dir_frm, dir_to; //朝向

public:
    DirectedDeviceBase(int _x, int _y, Direction _dir_frm, Direction _dir_to, CoreAdapter *_adapter);
    virtual ~DirectedDeviceBase();
    virtual void rotate() = 0;
    virtual void deliverObj();
};

bool checkFrmTo(const DirectedDeviceBase *, const BlockBase *);

const int DIR_OFF[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
} // namespace Block

#endif
