#include "Core/Core.h"
#include "Core/CoreAdapter.h"

Core::Core() :
    cnt_obj1(0),
    cnt_obj2(0),
    cnt_obj21(0),
    cnt_obj22(0),
    money(0),
    lvup(1),
    epnt(0.0), rate(1.0)
{
    adapter = new CoreAdapter(this);
}

Core::~Core() {
}

void Core::update(const int &_tick) {
    tick = _tick;
    map->update(tick);
}

int Core::getTick() const {
    return tick;
}

void Core::sellAll() {
    //int old_money = money;
    float off = rate * (cnt_obj1 * 10 + cnt_obj2 * 10 + cnt_obj21 * 5 + cnt_obj22 * 5);
    money += (int)off;
    adapter->Core_changeMoney(money);
    adapter->Center_changeObjCnt(1, -cnt_obj1);
    adapter->Center_changeObjCnt(2, -cnt_obj2);
    adapter->Center_changeObjCnt(21, -cnt_obj21);
    adapter->Center_changeObjCnt(22, -cnt_obj22);
}

void Core::increaseRate() {
    epnt += 0.1;
    rate = 3 - 2 * exp(-epnt);
    adapter->changeRate(rate);
}
