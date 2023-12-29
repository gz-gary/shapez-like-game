#include "Core/Map/Block/Miner.h"
using namespace Block;

int Block::Miner::glb_grade = 1;

Block::Miner::Miner(int _x, int _y, Direction _dir_to, CoreAdapter *_adapter) :
    DirectedDeviceBase(_x, _y, Direction::None, _dir_to, _adapter)
{
    this->grade = Block::Miner::glb_grade;
}

Block::Miner::~Miner()
{
}

std::string Block::Miner::getSymbStr() const
{
    char buffer[32];
    sprintf(buffer, "Miner %d", dir_to + 3);
    return buffer;
}

void Block::Miner::handleObj(int tick)
{
    double x0 = x - 0.5, y0 = y - 0.5,
           x1 = x0 + DIR_OFF[(int)dir_to][0] * 0.5,
           y1 = y0 + DIR_OFF[(int)dir_to][1] * 0.5;
    double x, y;
    int t;
    for (auto obj : obj_lis)
    {
        t = obj->pos;
        x = (x0 * (100 - t) + x1 * t) / 100.0;
        y = (y0 * (100 - t) + y1 * t) / 100.0; // linear move
        adapter->Device_moveMineObj(obj->id, x, y, obj->angle);
    }

    /* produce new object */
    if (tick % (21 - grade * 3) == 0 && obj_lis.size() == 0)
        append(src->produce());
}

void Block::Miner::rotate()
{
}

void Block::Miner::upgrade() {
    ++grade;
}
