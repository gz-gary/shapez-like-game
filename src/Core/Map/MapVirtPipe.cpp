#include "Core/Map/Map.h"
#include "Core/Map/Block/Direction.h"
#include <vector>
using namespace Block;

void Map::drawPipeLis(std::stack<std::pair<int, int>> p) {
    
    std::list<PipeLisObj> lis;
    while (!p.empty()) {
        lis.push_back({p.top().first, p.top().second, Direction("Up"), Direction("Down")});
        p.pop();
    }
    auto lend = lis.rbegin();
    while (lend != lis.rend() &&
           isBlockEmpty(lend->x, lend->y)) {
        ++lend;
    }
    if (lend == lis.rbegin()) return;
    auto lst = std::prev(lend);
    for (auto iter = std::next(lis.rbegin()); iter != lst; ++iter) {
        auto a = std::prev(iter), b = std::next(iter);
        for (int k = 0; k < 4; ++k) {
            if (iter->x + DIR_OFF[k][0] == a->x &&
                iter->y + DIR_OFF[k][1] == a->y) {
                iter->dir_frm = k;
            }
            if (iter->x + DIR_OFF[k][0] == b->x &&
                iter->y + DIR_OFF[k][1] == b->y) {
                iter->dir_to = k;
            }
        }
        //printf("(%d,%d,%s,%s),", iter->x, iter->y, iter->dir_frm.getStr().c_str(), iter->dir_to.getStr().c_str());
    }
    auto b = std::next(lis.rbegin()), iter = lis.rbegin();
    int flag = 1;
    if (b == lis.rend()) return;
    for (int k = 0; k < 4; ++k) {
        if (iter->x + DIR_OFF[k][0] == b->x &&
            iter->y + DIR_OFF[k][1] == b->y) {
            iter->dir_to = k;
            break;
        }
    }

    for (int k = 0; k < 4; ++k) {
        auto nbr = getBlock(iter->x, iter->y)->neighbor[k];
        auto ddvc = qobject_cast<DirectedDeviceBase*>(nbr);
        if (ddvc && ddvc->dir_to.reverse() == k) {
            iter->dir_frm = k;
            flag = 0;
            break;
        }
    }
    if (flag) iter->dir_frm = iter->dir_to.reverse();
    //printf("(%d,%d,%s,%s),", iter->x, iter->y, iter->dir_frm.getStr().c_str(), iter->dir_to.getStr().c_str());

    iter = lst, flag = 1;
    auto a = std::prev(iter);
    for (int k = 0; k < 4; ++k) {
        if (iter->x + DIR_OFF[k][0] == a->x &&
            iter->y + DIR_OFF[k][1] == a->y) {
            iter->dir_frm = k;
            break;
        }
    }

    for (int k = 0; k < 4; ++k) {
        auto nbr = getBlock(iter->x, iter->y)->neighbor[k];
        auto dvc = qobject_cast<DeviceBase*>(nbr);
        auto ddvc = qobject_cast<DirectedDeviceBase*>(nbr);
        if (dvc && !ddvc) {
            iter->dir_to = k;
            flag = 0;
            break;
        }
    }
    if (flag) {
        for (int k = 0; k < 4; ++k) {
            auto nbr = getBlock(iter->x, iter->y)->neighbor[k];
            auto ddvc = qobject_cast<DirectedDeviceBase*>(nbr);
            if (ddvc && ddvc->dir_frm.reverse() == k) {
                iter->dir_to = k;
                flag = 0;
                break;
            }
        }
    }
    if (flag) iter->dir_to = iter->dir_frm.reverse();

    while (!virt_pipe_buffer.empty()) virt_pipe_buffer.pop();
    for (auto ptr = lis.rbegin(); ptr != lend; ++ptr) virt_pipe_buffer.push(*ptr);
    adapter->drawVirtPipeLis(virt_pipe_buffer);
}

void Map::confirmVirt() {
    while (!virt_pipe_buffer.empty()) {
        auto tp = virt_pipe_buffer.top();
        auto pipe = new Pipe(tp.x, tp.y, tp.dir_frm, tp.dir_to, adapter);
        setBlock(tp.x, tp.y, pipe);
        virt_pipe_buffer.pop();
    }
}


