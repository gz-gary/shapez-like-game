#ifndef __GAME_H__
#define __GAME_H__

#include "common.h"
#include "Timer/Timer.h"
#include "Core/Core.h"
#include "GUI/GUI.h"

class Game : public QObject {

    Q_OBJECT;

public:
    Game();
    ~Game();

    void init();
    void initTimer();
    void initCore();
    void initGUI();

    void restart(const char *path_savefile);

    int getTick() const;

private:
    int tick;
    Timer *timer;
    Core *core;
    GUI *gui;

public slots:
    void slot_globalUpdate();
    
};

#endif
