#include "Core/Map/Block/Rotater.h"

using namespace Block;
using namespace MineObject;

int Block::Rotater::glb_grade = 1;

Block::Rotater::Rotater(int _x, int _y, Direction _dir_to, int _alt, CoreAdapter *_adapter) :
    DirectedDeviceBase(_x, _y, _dir_to.reverse(), _dir_to, _adapter),
    alt(_alt)
{
    this->grade = Block::Rotater::glb_grade;

    char buffer[32];
    sprintf(buffer, "Rotater %d %d", dir_to + 3, alt);
    info.symb_str = buffer;
    info.x0 = x - 0.5, info.y0 = y - 0.5;
    info.x1 = info.x0 + DIR_OFF[(int)dir_to][0] * 0.5;
    info.y1 = info.y0 + DIR_OFF[(int)dir_to][1] * 0.5;
    info.x2 = info.x0 + DIR_OFF[(int)dir_frm][0] * 0.5;
    info.y2 = info.y0 + DIR_OFF[(int)dir_frm][1] * 0.5;

}

void Block::Rotater::upgrade()
{ ++grade; }

Block::Rotater::~Rotater()
{ }

std::string Block::Rotater::getSymbStr() const
{
    return info.symb_str;
}

void Block::Rotater::handleObj(int tick)
{
    float x, y;
    int t;
    for (auto obj : obj_lis)
    {
        t = obj->pos;
        if (!obj->dirty) {
            obj->origin_angle = obj->angle;
        }
        obj->angle = obj->origin_angle + (alt == 0 ? -1 : 1) * t / 100.0 * 90.0;

        x = (info.x2 * (100 - t) + info.x1 * t) / 100.0;
        y = (info.y2 * (100 - t) + info.y1 * t) / 100.0; // linear move
        adapter->Device_moveMineObj(obj->id, x, y, obj->angle);
    }
}

void Block::Rotater::rotate() {
}

