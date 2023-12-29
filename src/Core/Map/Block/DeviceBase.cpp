#include "Core/Map/Block/DeviceBase.h"
#include "Core/Map/Block/Cutter.h"
using namespace Block;

Block::DeviceBase::DeviceBase(int _x, int _y, CoreAdapter* _adapter) :
    BlockBase(_x, _y, _adapter),
    grade(1)
{ }

void Block::DeviceBase::resetDelivery() {
    obj_delivered = false;
}

int Block::DeviceBase::full() {
    return obj_lis.size() >= 2;
}

void Block::DeviceBase::append(MineObject::MineObjectBase *obj)
{
    if (!full())
        obj_lis.push_back(obj);
}

Block::DeviceBase::~DeviceBase()
{
    for (auto obj : obj_lis)
        delete obj;
    obj_lis.clear();
}

/* --------------------------- */

Block::DirectedDeviceBase::DirectedDeviceBase(int _x, int _y, Direction _dir_frm, Direction _dir_to, CoreAdapter *_adapter) :
    DeviceBase(_x, _y, _adapter), dir_frm(_dir_frm), dir_to(_dir_to)
{ }

void Block::DirectedDeviceBase::deliverObj()
{
    /* already finish delivery, recurse stopped here */
    if (obj_delivered) return;
    obj_delivered = true;

    /* get the target block by direction and neighbor array */
    BlockBase *blk_target = neighbor[(int)dir_to];

    /* using qobject_cast to identify the class of target block (RTTI) */
    DeviceBase *dvc_target = qcast(blk_target, Block::DeviceBase*);
    DirectedDeviceBase *ddvc_target;

    /* flag is set if this device can deliver object to the target */
    int flag = (blk_target != nullptr && Block::checkFrmTo(this, blk_target));
    if (flag)
    {
        if ((ddvc_target = qcast(blk_target, Block::DirectedDeviceBase*))) {
            /* recursively deliver */
            ddvc_target->deliverObj();
        }
    }

    /* move objects forward in this device, and append them to the target device if
     * flag is set and the object's pos is over than 100
     */

    auto prev = obj_lis.begin();
    for (auto iter = obj_lis.begin(); iter != obj_lis.end();)
    {
        auto tmp = iter++;
        auto obj = *tmp;
        if (!obj->dirty) obj->dirty = 1;

        obj->pos += grade * 4;
        if (tmp != obj_lis.begin()) {
            if ((obj->pos + 60) > ((*prev)->pos)) {
                obj->pos = (*prev)->pos - 60;
            }
        } else {
            int p1 = obj->pos;
            if (flag && !dvc_target->obj_lis.empty()) {
                int p2 = (*(dvc_target->obj_lis.rbegin()))->pos;
                if (p1 + 60 - 100 > p2) {
                    p1 = p2 + 100 - 60;
                    obj->pos = p1;
                }
            }
        }
        if (obj->pos >= 100)
        {
            if (flag && !(dvc_target->full()))
            {
                if (qcast(dvc_target, Block::Cutter*))
                {
                    if (qcast(obj, MineObject::MineObject2*))
                    {
                        obj->pos = 0;
                        obj->angle = std::round((obj->angle) / 90.0) * 90;
                        obj->dirty = 0;
                        dvc_target->append(obj);
                        obj_lis.erase(tmp);
                    }
                    else
                        obj->pos = 100;
                }
                else
                {
                    obj->pos -= 100;
                    obj->angle = std::round((obj->angle) / 90.0) * 90;
                    obj->dirty = 0;
                    dvc_target->append(obj);
                    obj_lis.erase(tmp);
                }
            }
            else
                obj->pos = 100;
        }

        prev = tmp;
    }
}

Block::DirectedDeviceBase::~DirectedDeviceBase()
{
}

/* --------------------------- */

bool Block::checkFrmTo(const DirectedDeviceBase *blk_frm, const BlockBase *blk_to)
{
    if (qcast(blk_to, const Block::DirectedDeviceBase*)) // target is Directed
    {
        const DirectedDeviceBase *dvc_frm = blk_frm;
        auto *dvc_to = qobject_cast<const DirectedDeviceBase *>(blk_to);
        if (dvc_to->dir_frm == Direction("None")) // target has no source
            return false;
        else {
            return (dvc_frm->neighbor[(int)(dvc_frm->dir_to)] == blk_to) &&
                   (dvc_to->neighbor[(int)(dvc_to->dir_frm)] == blk_frm); // connected
        }
    }
    else if (qcast(blk_to, const Block::DeviceBase*)) // target is a normal Device
        return true;
    else
        return false;
}
