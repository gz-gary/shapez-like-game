#include "Core/Map/Block/Cutter.h"

using namespace Block;
using namespace MineObject;

int Block::Cutter::glb_grade = 1;

Block::Cutter::Cutter(int _x, int _y, Direction _dir_frm, Direction _dir_to, int _alt, CoreAdapter *_adapter) :
    DirectedDeviceBase(_x, _y, _dir_frm, _dir_to, _adapter),
    alt(_alt)
{
    this->grade = Block::Cutter::glb_grade;

    char buffer[32];
    sprintf(buffer, "Cutter %d %d", dir_to + 3, alt);
    info.symb_str = buffer;
    info.x0 = x - 0.5, info.y0 = y - 0.5;
    info.x1 = info.x0 + DIR_OFF[(int)dir_to][0] * 0.5, info.y1 = info.y0 + DIR_OFF[(int)dir_to][1] * 0.5;
    if (alt == 0) {
        info.x2 = info.x0 + DIR_OFF[(int)dir_frm][0] * 0.5;
        info.y2 = info.y0 + DIR_OFF[(int)dir_frm][1] * 0.5;
    } else {
        int idFrm = (int)(dir_to.reverse());
        info.x2 = info.x0 + DIR_OFF[idFrm][0] * 0.5;
        info.y2 = info.y0 + DIR_OFF[idFrm][1] * 0.5;
    }
}

void Block::Cutter::upgrade()
{ ++grade; }

Block::Cutter::~Cutter()
{ }

void Block::Cutter::resetDelivery() {
    DeviceBase::resetDelivery();
    obj_cut = false;
}

std::string Block::Cutter::getSymbStr() const
{
    return info.symb_str;
}

void Block::Cutter::handleObj(int tick)
{
    if (obj_cut)
        return;

    if (alt == 0)
    { // Main
        for (auto iter = obj_lis.begin(); iter != obj_lis.end();)
        {
            auto tmp = iter++;
            if (qcast(*tmp, MineObject::MineObject2*))
            { // split obj2
                adapter->Device_removeMineObj((*tmp)->id);
                delete (*tmp);
                obj_lis.erase(tmp);

                if (!full())
                {
                    auto a = new MineObject21(adapter);
                    adapter->All_newMineObj(a->id, a->getSymbStr());
                    append(a);
                }
                if (!(couple->full()))
                {
                    auto b = new MineObject22(adapter);
                    adapter->All_newMineObj(b->id, b->getSymbStr());
                    couple->append(b);
                }

                // split obj2
            }
        }
    }
    else if (alt == 1)
    { // Vice
        couple->handleObj(tick);
    }

    float x, y;
    int t;
    for (auto obj : obj_lis)
    {
        t = obj->pos;
        x = (info.x2 * (100 - t) + info.x1 * t) / 100.0;
        y = (info.y2 * (100 - t) + info.y1 * t) / 100.0; // linear move
        adapter->Device_moveMineObj(obj->id, x, y, obj->angle);
    }

    obj_cut = true;
}

void Block::Cutter::rotate()
{
    ++grade;
}
