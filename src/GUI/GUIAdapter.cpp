#include "GUI/GUIAdapter.h"
#include "GUI/GUI.h"
#include "Core/Map/Block/Direction.h"
#include <QTransform>
#include <QPixmap>
#include <QMatrix>
#include <QString>
#include <QLabel>
#include <sstream>
#include <string>
#include <QColor>
#include <QTransform>

GUIAdapter::GUIAdapter(GUI *_gui) :
    gui(_gui)
{
}
GUIAdapter::~GUIAdapter() {
}

void GUIAdapter::slot_setBlock(int x, int y, std::string symb) {
    std::istringstream in_str(symb);
    std::string type, dir, ret;
    int tmp, alt;

    in_str >> type;
    auto ptr = gui->play_widget->lbl_mat[x][y];
    auto parent = gui->play_widget->lbl_bkg[x][y];
    if (type == "Trashbin") {
        ptr->setPixmap(*gui->trashbin);
        ptr->adjustSize();
        ptr->type = 0;
        ptr->raise();
        ptr->show();
        ptr->move(parent->pos());
    } else if (type == "Pipe") {
        in_str >> dir >> tmp;
        if (dir == "forward") {
            ptr->setPixmap(*gui->belt_forward[tmp % 4][gui->tick % 14]);
            ptr->type = 1;
        } else if (dir == "left") {
            ptr->setPixmap(*gui->belt_left[tmp % 4][gui->tick % 14]);
            ptr->type = 2;
        } else if (dir == "right") {
            ptr->setPixmap(*gui->belt_right[tmp % 4][gui->tick % 14]);
            ptr->type = 3;
        }
        ptr->dir = tmp % 4;
        ptr->adjustSize();
        ptr->raise();
        ptr->show();
        ptr->move(parent->pos());
    } else if (type == "Cutter") {
        in_str >> tmp >> alt;
        ptr->setPixmap(*gui->cutter[tmp % 4][alt]);
        ptr->type = 4;
        ptr->adjustSize();
        ptr->raise();
        ptr->show();
        ptr->move(parent->pos());
    } else if (type == "Mine1") {
        ptr->setPixmap(*gui->mine1);
        ptr->type = 5;
        if (ptr->lbl_top) {
            delete ptr->lbl_top;
            ptr->lbl_top = nullptr;
        }
        int tx = parent->pos().x(), ty = parent->pos().y();
        ptr->type = 0;
        ptr->move(tx + 12, ty + 12);
        ptr->adjustSize();
        ptr->raise();
        ptr->show();
    } else if (type == "Mine2") {
        ptr->setPixmap(*gui->mine2);
        ptr->type = 6;
        if (ptr->lbl_top) {
            delete ptr->lbl_top;
            ptr->lbl_top = nullptr;
        }
        auto parent = gui->play_widget->lbl_bkg[x][y];
        int tx = parent->pos().x(), ty = parent->pos().y();
        ptr->type = 0;
        ptr->move(tx + 12, ty + 12);
        ptr->adjustSize();
        ptr->raise();
        ptr->show();
    } else if (type == "Miner") {
        in_str >> tmp;
        auto lbl = new QLabel(gui->play_widget);
        lbl->setPixmap(*(gui->miner[tmp % 4]));
        int tx = ptr->pos().x(), ty = ptr->pos().y();
        ptr->type = 0;
        lbl->move(tx - 12, ty - 12);
        lbl->show();
        lbl->adjustSize();
        ptr->lbl_top = lbl;
        ptr->lbl_top = lbl;
    } else if (type == "Center") {
        ptr->setPixmap(*gui->center);
        ptr->adjustSize();
        ptr->type = 0;
        ptr->raise();
        ptr->show();
        ptr->move(parent->pos());
    } else if (type == "Rotater") {
        in_str >> tmp >> alt;
        if (alt == 0) ptr->setPixmap(*gui->rotater[tmp % 4]);
        else ptr->setPixmap(*gui->rotater_ccw[tmp % 4]);
        ptr->adjustSize();
        ptr->type = 0;
        ptr->raise();
        ptr->show();
        ptr->move(parent->pos());

    } else if (type == "Empty") {
        if (ptr->lbl_top) {
            delete ptr->lbl_top;
            ptr->lbl_top = nullptr;
        }
        ptr->hide();
    } else {
        ptr->setText(symb.c_str());
        ptr->adjustSize();
        ptr->type = 0;
    }
}

void GUIAdapter::slot_changeObjCnt(int type, int off) {
    auto tmp = gui->store_widget->lbl_obj_text;
    int ind;
    switch (type) {
    case 1:
        ind = 0;
        break;
    case 2:
        ind = 1;
        break;
    case 21:
        ind = 2;
        break;
    case 22:
        ind = 3;
        break;
    }
    tmp[ind]->setText(std::to_string(off).c_str());
    tmp[ind]->adjustSize();
}

void GUIAdapter::slot_changeMoney(int new_money) {
    auto lbl = gui->store_widget->lbl_money_text;
    lbl->setText(std::to_string(new_money).c_str());
    lbl->adjustSize();
}

void GUIAdapter::slot_newMineObj(int id, std::string symb) {
    auto tmp = new QLabel(gui->play_widget);
    if (symb == "*") {
        tmp->setPixmap(*gui->mine_obj1);
        gui->obj_origin_pix[id] = gui->mine_obj1;
    } else if (symb == "o") {
        tmp->setPixmap(*gui->mine_obj2);
        gui->obj_origin_pix[id] = gui->mine_obj2;
    } else if (symb == "+") {
        tmp->setPixmap(*gui->mine_obj21);
        gui->obj_origin_pix[id] = gui->mine_obj21;
    } else if (symb == "-") {
        tmp->setPixmap(*gui->mine_obj22);
        gui->obj_origin_pix[id] = gui->mine_obj22;
    } else {
        tmp->setText(symb.c_str());
    }
    tmp->adjustSize();
    gui->obj_map[id] = tmp;
    tmp->raise();
    tmp->hide();
}

void GUIAdapter::slot_moveMineObj(int id, float x, float y) {
    auto tmp = gui->obj_map[id];
    int w0 = 50;
    int h0 = 50;
    tmp->move(x * w0 - tmp->width() / 2, y * h0 - tmp->height() / 2);
    tmp->raise();
    tmp->show();
}

void GUIAdapter::slot_moveMineObj(int id, float x, float y, int angle) {
    auto tmp = gui->obj_map[id];
    auto pix = gui->obj_origin_pix[id];
    tmp->setPixmap(gui->smoothRotate(*pix, angle));
    tmp->adjustSize();
    int w0 = 50;
    int h0 = 50;
    tmp->move(x * w0 - tmp->width() / 2, y * h0 - tmp->height() / 2);
    tmp->raise();
    tmp->show();
}

void GUIAdapter::slot_removeMineObj(int id) {
    auto tmp = gui->obj_map[id];
    delete tmp;
    gui->obj_map.erase(id);
    gui->obj_origin_pix.erase(id);
}
 
void GUIAdapter::GUI_setDevice(int x, int y, int type, int dir) {
    dir %= 4;
    std::string info;
    Block::Direction dir1("Up"), dir2("Down");
    switch (type) {
    case 1:
        emit signal_setDevice(x, y, "Trashbin");
        break;
    case 2:
        dir1 = Block::Direction("Down");
        dir2 = Block::Direction("Up");

        while (dir > 0) {
            dir1 = dir1.rotate();
            dir2 = dir2.rotate();
            --dir;
        }
        info = "Pipe " + dir1.getStr() + " " + dir2.getStr();
        emit signal_setDevice(x, y, info);
        break;
    case 3:
        dir1 = Block::Direction("Down");
        dir2 = Block::Direction("Left");

        while (dir > 0) {
            dir1 = dir1.rotate();
            dir2 = dir2.rotate();
            --dir;
        }
        info = "Pipe " + dir1.getStr() + " " + dir2.getStr();
        emit signal_setDevice(x, y, info);
        break;
    case 4:
        dir1 = Block::Direction("Down");
        dir2 = Block::Direction("Right");

        while (dir > 0) {
            dir1 = dir1.rotate();
            dir2 = dir2.rotate();
            --dir;
        }
        info = "Pipe " + dir1.getStr() + " " + dir2.getStr();
        emit signal_setDevice(x, y, info);
        break;

    case 5:
        dir1 = Block::Direction("Up");

        while (dir > 0) {
            dir1 = dir1.rotate();
            --dir;
        }
        info = "Cutter 0 " + dir1.getStr();
        emit signal_setDevice(x, y, info);
        break;

    case 6:
        dir1 = Block::Direction("Up");

        while (dir > 0) {
            dir1 = dir1.rotate();
            --dir;
        }
        info = "Miner " + dir1.getStr();
        emit signal_setDevice(x, y, info);
        break;

    case 7:
        emit signal_setDevice(x, y, "Remove");
        break;

    case 8:
        emit signal_setDevice(x, y, "Upgrade");
        break;
    case 9:
        emit signal_setDevice(x, y, "Confirm");
        break;
    case 10:
    case 11:
        int alt = type - 10;
        dir1 = Block::Direction("Up");

        while (dir > 0) {
            dir1 = dir1.rotate();
            --dir;
        }
        info = "Rotater " + std::to_string(alt) + " " + dir1.getStr();
        emit signal_setDevice(x, y, info);
        break;

    }
}

void GUIAdapter::slot_displayInfo(Info type) {
    std::string text;
    QColor col;
    switch (type) {
    case Info::Error_NotEmpty:
        //text = "[Map]: Operation Failed! Some block is not empty.";
        text = "操作失败！没有足够的空间放置设备。";
        col = Qt::red;
        break;
    case Info::Error_MinerOnMine:
        //text = "[Map]: Operation Failed! Miner must be set on mine.";
        text = "操作失败！开采器只能放置在开采物地块上。";
        col = Qt::red;
        break;
    case Info::Error_RemoveMine:
        //text = "[Map]: Operation Failed! Cannot remove mine.";
        text = "操作失败！不能移除开采物。";
        col = Qt::red;
        break;
    case Info::Error_RemoveCenter:
        //text = "[Map]: Operation Failed! Cannot remove center.";
        text = "操作失败！不能移除交付中心。";
        col = Qt::red;
        break;
    case Info::Error_NoUpgradeChance:
        //text = "[Core]: Operation Failed! No upgrade chance.";
        text = "操作失败！没有足够的强化次数。请完成更多任务以获得强化次数。";
        col = Qt::red;
        break;
    case Info::Info_UpgradePipe:
        //text = "[Core]: Upgrade Pipe.";
        text = "[传送带] 已强化";
        col = Qt::green;
        break;
    case Info::Info_UpgradeMiner:
        text = "[开采器] 已强化";
        col = Qt::green;
        break;
    case Info::Info_UpgradeCutter:
        text = "[切割机] 已强化";
        col = Qt::green;
        break;
    case Info::Info_Mission1Complete:
        text = "[任务1] 已完成！获得1个 [强化次数]";
        col = Qt::blue;
        break;
    case Info::Info_Mission2Complete:
        text = "[任务2] 已完成！获得1个 [强化次数]";
        col = Qt::blue;
        break;
    case Info::Info_Mission3Complete:
        text = "[任务3] 已完成！获得1个 [强化次数]";
        col = Qt::blue;
        break;
    case Info::Info_Mission4Complete:
        text = "[任务4] 已完成！获得1个 [强化次数]";
        col = Qt::blue;
        break;
    case Info::Error_NotUpgradable:
        //text = "[Core]: Operation Failed! Device is not upgradable.";
        text = "操作失败！该设备不可强化。";
        col = Qt::red;
        break;
    case Info::Error_NoSpaceToExpandCenter:
        //text = "[Core]: Operation Failed! No enough space to expand Center.";
        text = "操作失败！没有足够的空间扩展交付中心。请移除交付中心周围的设备。";
        col = Qt::red;
        break;
    case Info::Info_ExpandCenter:
        //text = "[Core]: Expand center.";
        text = "[交付中心] 已扩展";
        col = Qt::green;
        break;
    case Info::Error_NoEnoughMoney:
        //text = "[Core]: Operation Failed! No enough money to buy item.";
        text = "操作失败！没有足够的金钱购买该物品。请赚取更多金钱。";
        col = Qt::red;
        break;
    case Info::Info_ExpandMap:
        text = "[地图] 已扩展";
        col = Qt::green;
        break;
 
    }
    gui->msg_widget->pushMsg(text, col);
    //gui->lbl_debug_info->setText(text.c_str());
    //gui->lbl_debug_info->adjustSize();
}

void GUIAdapter::slot_changeLvup(int now) {
    auto new_text = std::to_string(now);
    gui->toolbar_widget->lbl_lvup->setText(new_text.c_str());
}

void GUIAdapter::Store_buyItem(int type) {
    emit signal_buyItem(type);
}

void GUIAdapter::slot_changeMapSize(int w, int h) {
    gui->play_widget->resize(w * 50, h * 50);
    gui->play_widget->move(0, 0);
}

void GUIAdapter::Menu_saveGame(const char *path) {
    emit signal_saveGame(path);
}

void GUIAdapter::Menu_reloadGame(const char *path) {
    emit signal_reloadGame(path);
}

void GUIAdapter::slot_changeRate(float now) {
    char buffer[64];
    sprintf(buffer, "倍率: %.2lf", now);
    gui->store_widget->lbl_rate->setText(buffer);
    gui->store_widget->lbl_rate->adjustSize();
}

void GUIAdapter::GUI_drawPipeLis(std::stack<std::pair<int, int>> p) {
    emit signal_drawPipeLis(p);
}

void GUIAdapter::slot_drawVirtPipeLis(std::stack<PipeLisObj> stk) {
    gui->play_widget->drawVirtPipe(stk);
}
