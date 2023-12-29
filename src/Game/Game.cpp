#include "Game/Game.h"
#include <stack>

Game::Game() :
    timer(nullptr),
    core(nullptr),
    gui(nullptr)
{
    
}

Game::~Game() {
    delete timer;
    delete core;
    delete gui;
}

void Game::init() {
}

void Game::restart(const char *path_savefile) {
    srand(time(0));
    initTimer();
    connect(timer, SIGNAL(signal_externalTimeout()), this, SLOT(slot_globalUpdate()));
    initCore();
    initGUI();
    connect(core->adapter, SIGNAL(signal_setBlock(int, int, std::string)),
            gui->adapter, SLOT(slot_setBlock(int, int, std::string)));
    connect(core->adapter, SIGNAL(signal_newMineObj(int, std::string)),
            gui->adapter, SLOT(slot_newMineObj(int, std::string)));
    connect(core->adapter, SIGNAL(signal_moveMineObj(int, float, float)),
            gui->adapter, SLOT(slot_moveMineObj(int, float, float)));
    connect(core->adapter, SIGNAL(signal_moveMineObj(int, float, float, int)),
            gui->adapter, SLOT(slot_moveMineObj(int, float, float, int)));
    connect(core->adapter, SIGNAL(signal_removeMineObj(int)),
            gui->adapter, SLOT(slot_removeMineObj(int)));
    connect(core->adapter, SIGNAL(signal_info(Info)),
            gui->adapter, SLOT(slot_displayInfo(Info)));
    connect(core->adapter, SIGNAL(signal_changeLvup(int)),
            gui->adapter, SLOT(slot_changeLvup(int)));
    connect(core->adapter, SIGNAL(signal_changeMoney(int)),
            gui->adapter, SLOT(slot_changeMoney(int)));
    connect(core->adapter, SIGNAL(signal_changeObjCnt(int, int)),
            gui->adapter, SLOT(slot_changeObjCnt(int, int)));
    connect(core->adapter, SIGNAL(signal_changeMapSize(int, int)),
            gui->adapter, SLOT(slot_changeMapSize(int, int)));
    connect(core->adapter, SIGNAL(signal_changeRate(float)),
            gui->adapter, SLOT(slot_changeRate(float)));
    connect(core->adapter, SIGNAL(signal_drawVirtPipeLis(std::stack<PipeLisObj>)),
            gui->adapter, SLOT(slot_drawVirtPipeLis(std::stack<PipeLisObj>)));
    connect(gui->adapter, SIGNAL(signal_setDevice(int, int, std::string)),
            core->adapter, SLOT(slot_setDevice(int, int, std::string)));
    connect(gui->adapter, SIGNAL(signal_buyItem(int)),
            core->adapter, SLOT(slot_buyItem(int)));
    connect(gui->adapter, SIGNAL(signal_saveGame(const char*)),
            core->adapter, SLOT(slot_saveGame(const char*)));
    connect(gui->adapter, SIGNAL(signal_reloadGame(const char*)),
            core->adapter, SLOT(slot_reloadGame(const char*)));
    connect(gui->adapter, SIGNAL(signal_drawPipeLis(std::stack<std::pair<int, int>>)),
            core->adapter, SLOT(slot_drawPipeLis(std::stack<std::pair<int, int>>)));
    connect(gui->menu_widget, &MenuWidget::signal_quit,
            this, [=](){exit(0);});
    core->load(path_savefile);
    gui->main_widget->show();

    //connect(core, SIGNAL());
    timer->start();
}

void Game::initCore() {
    if (core != nullptr) delete core;
    core = new Core;
}

void Game::initGUI() {
    if (gui != nullptr) delete gui;
    gui = new GUI;
}

