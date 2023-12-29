#ifndef __MINE_H__
#define __MINE_H__

#include "Core/Map/Block/BlockBase.h"
#include "Core/Map/MineObject/MineObject.h"

namespace Block
{
    enum class MineType {
        Mine1,
        Mine2
    };

class MineBase : public BlockBase {

    Q_OBJECT;

private:
    MineType type;

public:
    MineBase(int _x, int _y, CoreAdapter* _adapter, MineType _type);
    ~MineBase();
    virtual std::string getSymbStr() const = 0;
    virtual MineObject::MineObjectBase* produce() = 0;
    MineType getType() const;

};

class Mine1 : public MineBase
{

    Q_OBJECT;

public:
    Mine1(int _x, int _y, CoreAdapter* _adapter);
    ~Mine1();
    std::string getSymbStr() const;
    MineObject::MineObject1* produce();
};

class Mine2 : public MineBase
{
    Q_OBJECT;

public:
    Mine2(int _x, int _y, CoreAdapter* _adapter);
    ~Mine2();
    std::string getSymbStr() const;
    MineObject::MineObject2* produce();
};

} // namespace Block

#endif
