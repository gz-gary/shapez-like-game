#ifndef __PIPE_H__
#define __PIPE_H__

#include "Core/Map/Block/DeviceBase.h"

namespace Block
{

class Pipe : public DirectedDeviceBase
{

    Q_OBJECT;

    friend class ::Map;

private:
    static int glb_grade;

public:
    Pipe(int _x, int _y, Direction _dir_frm, Direction _dir_to, CoreAdapter *_adapter);
    ~Pipe();
    std::string getSymbStr() const;
    void handleObj(int tick);
    void upgrade();
    void rotate();
};

} // namespace Block

#endif
