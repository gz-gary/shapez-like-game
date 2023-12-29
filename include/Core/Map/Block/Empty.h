#ifndef __EMPTY_H__
#define __EMPTY_H__

#include "Core/Map/Block/BlockBase.h"

namespace Block
{

class Empty : public BlockBase
{

    Q_OBJECT;

public:
    Empty(int _x, int _y, CoreAdapter* _adapter);
    ~Empty();
    std::string getSymbStr() const;
};

} // namespace Block

#endif
