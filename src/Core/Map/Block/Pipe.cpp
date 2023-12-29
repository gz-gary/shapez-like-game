#include "Core/Map/Block/Pipe.h"
using namespace Block;

int Block::Pipe::glb_grade = 1;

Block::Pipe::Pipe(int _x, int _y, Direction _dir_frm, Direction _dir_to, CoreAdapter *_adapter) :
    DirectedDeviceBase(_x, _y, _dir_frm, _dir_to, _adapter)
{
    this->grade = Block::Pipe::glb_grade;
    char buffer[32];
    int ab = dir_frm - dir_to;
    if (ab == 2 || ab == -2) {
        sprintf(buffer, "Pipe forward %d", (int)(dir_to + 3));
    } else if (ab == -1 || ab == 3) {
        sprintf(buffer, "Pipe right %d", (int)dir_to);
    } else if (ab == 1 || ab == -3) {
        sprintf(buffer, "Pipe left %d", (int)(dir_to + 2));
    }
    info.symb_str = buffer;

    if (dir_to - dir_frm == -2 || dir_to - dir_frm == 2) {
        info.x0 = x - 0.5, info.y0 = y - 0.5;
        info.x1 = info.x0 + DIR_OFF[(int)dir_to][0] * 0.5;
        info.y1 = info.y0 + DIR_OFF[(int)dir_to][1] * 0.5;
        info.x2 = info.x0 + DIR_OFF[(int)dir_frm][0] * 0.5;
        info.y2 = info.y0 + DIR_OFF[(int)dir_frm][1] * 0.5;
        info.flag = 0;
    } else {
        info.x0 = x - 0.5 + DIR_OFF[(int)dir_to][0] * 0.5 + DIR_OFF[(int)dir_frm][0] * 0.5,
        info.y0 = y - 0.5 + DIR_OFF[(int)dir_to][1] * 0.5 + DIR_OFF[(int)dir_frm][1] * 0.5;
        info.dir = (dir_to - dir_frm + 4) % 4 == 3 ? 1 : -1;
        info.ori = PI + (int)dir_to * PI / 2;
        info.flag = 1;
    }
}

Block::Pipe::~Pipe()
{
}

std::string Block::Pipe::getSymbStr() const
{
    return info.symb_str;
}

void Block::Pipe::handleObj(int tick)
{
    /* figure out object's position to display according to the
     * properties of this pipe block.
     *
     * properties are calculated during construction.
     *
     * here the x and y is the position of core coordinate
     * which need to be transformed to screen coord by GUI.
     */

    if (!info.flag) { /* straight pipe, linear move */
        float x, y;
        int t;
        for (auto obj : obj_lis)
        {
            t = obj->pos;
            /* linear interpolation */
            x = (info.x2 * (100 - t) + info.x1 * t) / 100.0;
            y = (info.y2 * (100 - t) + info.y1 * t) / 100.0;
            adapter->Device_moveMineObj(obj->id, x, y, obj->angle);
        }
    } else { /* round pipe, move along an arc of a circle */
        float x, y, c, s, theta;
        int t;
        for (auto obj : obj_lis)
        {
            t = obj->pos;
            /* triangular calculation */
            theta = info.ori + PI / 2 * (t / 100.0) * info.dir;
            c = cos(theta);
            s = sin(theta);
            x = info.x0 + c * 0.5;
            y = info.y0 - s * 0.5;
            adapter->Device_moveMineObj(obj->id, x, y, obj->angle);
        }
    }
}

void Block::Pipe::rotate()
{
}

void Block::Pipe::upgrade() {
    ++grade;
}
