#ifndef __CORE_ADAPTER_H__
#define __CORE_ADAPTER_H__

#include "common.h"
#include <stack>

class Core;

class CoreAdapter : public QObject {

    Q_OBJECT;

    friend class Map;

public:
    CoreAdapter(Core *_core);
    CoreAdapter(CoreAdapter &&) = default;
    CoreAdapter(const CoreAdapter &) = default;
    CoreAdapter &operator=(CoreAdapter &&) = default;
    CoreAdapter &operator=(const CoreAdapter &) = default;
    ~CoreAdapter();

private:
    Core *core;

public:
    void Map_setBlock(int x, int y, std::string symb);
    void Center_changeObjCnt(int type, int off);
    void Core_changeObjCnt(int type, int off);
    void Core_changeMoney(int new_money);
    void All_newMineObj(int id, std::string symb);
    void Device_moveMineObj(int id, float x, float y);
    void Device_moveMineObj(int id, float x, float y, int angle);
    void Device_removeMineObj(int id);
    void All_raiseInfo(Info type);
    void All_changeLvup(int now);
    void Map_changeMapSize(int w, int h);
    void changeRate(float now);
    void drawVirtPipeLis(std::stack<PipeLisObj> stk);

signals:
    void signal_setBlock(int x, int y, std::string symb);
    void signal_changeObjCnt(int type, int off);
    void signal_changeMoney(int new_money);
    void signal_newMineObj(int id, std::string symb);
    void signal_moveMineObj(int id, float x, float y);
    void signal_moveMineObj(int id, float x, float y, int angle);
    void signal_removeMineObj(int id);
    void signal_info(Info type);
    void signal_changeLvup(int now);
    void signal_changeMapSize(int w, int h);
    void signal_changeRate(float now);
    void signal_drawVirtPipeLis(std::stack<PipeLisObj> stk);

public slots:
    void slot_setDevice(int x, int y, std::string info);
    void slot_buyItem(int type);
    void slot_saveGame(const char *path);
    void slot_reloadGame(const char *path);
    void slot_drawPipeLis(std::stack<std::pair<int, int>> p);
    
};

#endif
