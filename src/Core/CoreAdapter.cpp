#include "Core/CoreAdapter.h"
#include "Core/Core.h"
#include "common.h"

CoreAdapter::CoreAdapter(Core *_core) :
    core(_core)
{
}

CoreAdapter::~CoreAdapter() {
}

void CoreAdapter::Center_changeObjCnt(int type, int off) {
    switch (type) {
        case 1:
            core->cnt_obj1 += off;
            if (core->total_cnt_obj1 >= 0) {
                core->total_cnt_obj1 += off;
                if (core->total_cnt_obj1 >= 30) {
                    core->total_cnt_obj1 = -1;
                    ++core->lvup;
                    emit signal_info(Info::Info_Mission1Complete);
                    All_changeLvup(core->lvup);
                }
            }
            emit signal_changeObjCnt(type, core->cnt_obj1);
            break;
        case 2:
            core->cnt_obj2 += off;
            if (core->total_cnt_obj2 >= 0) {
                core->total_cnt_obj2 += off;
                if (core->total_cnt_obj2 >= 20) {
                    core->total_cnt_obj2 = -1;
                    ++core->lvup;
                    emit signal_info(Info::Info_Mission2Complete);
                    All_changeLvup(core->lvup);
                }
            }
            emit signal_changeObjCnt(type, core->cnt_obj2);
            break;
        case 21:
            core->cnt_obj21 += off;
            if (core->total_cnt_obj21 >= 0) {
                core->total_cnt_obj21 += off;
                if (core->total_cnt_obj21 >= 20) {
                    core->total_cnt_obj21 = -1;
                    ++core->lvup;
                    emit signal_info(Info::Info_Mission3Complete);
                    All_changeLvup(core->lvup);
                }
            }
            emit signal_changeObjCnt(type, core->cnt_obj21);
            break;
        case 22:
        case 221:
            core->cnt_obj22 += off;
            core->total_cnt_obj22 += off;
            if (type == 221) {
                if (core->total_cnt_obj22_rot >= 0) {
                    core->total_cnt_obj22_rot += off;
                    if (core->total_cnt_obj22_rot >= 30) {
                        core->total_cnt_obj22_rot = -1;
                        ++core->lvup;
                        emit signal_info(Info::Info_Mission4Complete);
                        All_changeLvup(core->lvup);
                    }
                }
            }
            emit signal_changeObjCnt(22, core->cnt_obj22);
            break;
        default:
            break;
    }
}

void CoreAdapter::Map_setBlock(int x, int y, std::string symb) {
    emit signal_setBlock(x, y, symb);
    //std::cout << "[CoreAdapter::Map_setBlock]: Receiving Info!\n";
    //std::cout << x << " " << y << " " << symb << "\n\n";
}

void CoreAdapter::Core_changeObjCnt(int type, int off) {
    //std::cout << "[CoreAdapter::Core_changeObjCnt]: Receiving Info!\n";
    //std::cout << type << " " << off << "\n\n";
}

void CoreAdapter::Core_changeMoney(int new_money) {
    emit signal_changeMoney(new_money);
    //std::cout << "[CoreAdapter::Core_changeMoney]: Receiving Info!\n";
    //std::cout << new_money << "\n\n";
}
void CoreAdapter::All_newMineObj(int id, std::string symb) {
    emit signal_newMineObj(id, symb);
}

void CoreAdapter::Device_moveMineObj(int id, float x, float y) {
    emit signal_moveMineObj(id, x, y);
}

void CoreAdapter::Device_moveMineObj(int id, float x, float y, int angle) {
    emit signal_moveMineObj(id, x, y, angle);
}

void CoreAdapter::Device_removeMineObj(int id) {
    emit signal_removeMineObj(id);
}

void CoreAdapter::slot_setDevice(int x, int y, std::string info) {
    //printf("%d %d %s\n", x, y, info.c_str());
    core->map->setDevice(x, y, info);
}

void CoreAdapter::slot_buyItem(int type) {
    switch (type) {
    case 1:
        if (core->money < 5000) {
            All_raiseInfo(Info::Error_NoEnoughMoney);
        }
        else if (!core->map->expandCenter()) {
            core->money -= 5000;
            Core_changeMoney(core->money);
        }
        break;
    case 2:
        if (core->money < 4000) {
            All_raiseInfo(Info::Error_NoEnoughMoney);
            return;
        }
        core->map->expandMine();
        core->money -= 4000;
        Core_changeMoney(core->money);
        break;
    case 3:
        if (core->money < 10000) {
            All_raiseInfo(Info::Error_NoEnoughMoney);
            return;
        }
        core->map->expandMap();
        core->money -= 10000;
        Core_changeMoney(core->money);
        break;
    case 4:
        if (core->money < 20000) {
            All_raiseInfo(Info::Error_NoEnoughMoney);
            return;
        }
        core->increaseRate();
        core->money -= 20000;
        Core_changeMoney(core->money);
        break;
    case 8:
        core->sellAll();
        break;
    }
}

void CoreAdapter::All_raiseInfo(Info type) {
    emit signal_info(type);
}

void CoreAdapter::All_changeLvup(int now) {
    emit signal_changeLvup(core->lvup);
}

void CoreAdapter::Map_changeMapSize(int w, int h) {
    emit signal_changeMapSize(w, h);
}

void CoreAdapter::slot_saveGame(const char *path) {
    if (strlen(path))
        core->save(path);
}

void CoreAdapter::slot_reloadGame(const char *path) {
    if (strlen(path))
        core->reload(path);
}

void CoreAdapter::changeRate(float now) {
    emit signal_changeRate(now);
}

void CoreAdapter::slot_drawPipeLis(std::stack<std::pair<int, int>> p) {
    core->map->drawPipeLis(p);
}

void CoreAdapter::drawVirtPipeLis(std::stack<PipeLisObj> stk) {
    emit signal_drawVirtPipeLis(stk);
}
