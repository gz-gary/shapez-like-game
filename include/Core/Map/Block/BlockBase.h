#ifndef __BLOCK_BASE_H__
#define __BLOCK_BASE_H__

#include "common.h"
#include "Core/CoreComponent.h"

class Map;

namespace Block
{

class BlockBase : public CoreComponent {

    Q_OBJECT;

friend class ::Map;

protected:
    int x, y; //坐标
    BlockBase *neighbor[4];

public:
    BlockBase(int _x, int _y, CoreAdapter* _adapter);
    virtual ~BlockBase();
    virtual std::string getSymbStr() const = 0;
};

} // namespace Block

#endif
