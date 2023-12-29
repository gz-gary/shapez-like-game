#ifndef __GUI_ADAPTER_H__
#define __GUI_ADAPTER_H__

#include "common.h"
#include <stack>

class GUI;
class ToolbarWidget;

class GUIAdapter : public QObject {

    Q_OBJECT;

    friend class ToolbarWidget;
    friend class StoreWidget;
    friend class MenuWidget;
    friend class MainWidget;
    friend class BlockLabel;
    friend class PlayWidget;

public:
    GUIAdapter(GUI *_gui);
    GUIAdapter(GUIAdapter &&) = default;
    GUIAdapter(const GUIAdapter &) = default;
    GUIAdapter &operator=(GUIAdapter &&) = default;
    GUIAdapter &operator=(const GUIAdapter &) = default;
    ~GUIAdapter();

private:
    GUI *gui;

public:
    void GUI_setDevice(int x, int y, int type, int dir);
    void Store_buyItem(int type);
    void Menu_saveGame(const char *path);
    void Menu_reloadGame(const char *path);
    void GUI_drawPipeLis(std::stack<std::pair<int, int>> p);

public slots:
    void slot_setBlock(int x, int y, std::string symb);
    void slot_changeObjCnt(int type, int off);
    void slot_changeMoney(int new_money);
    void slot_newMineObj(int id, std::string symb);
    void slot_moveMineObj(int id, float x, float y);
    void slot_moveMineObj(int id, float x, float y, int angle);
    void slot_removeMineObj(int id);
    void slot_displayInfo(Info type);
    void slot_changeLvup(int now);
    void slot_changeMapSize(int w, int h);
    void slot_changeRate(float now);
    void slot_drawVirtPipeLis(std::stack<PipeLisObj> stk);

signals:
    void signal_setDevice(int x, int y, std::string info);
    void signal_buyItem(int type);
    void signal_saveGame(const char *path);
    void signal_reloadGame(const char *path);
    void signal_increaseRate();
    void signal_drawPipeLis(std::stack<std::pair<int, int>> p);
    
};

#endif
