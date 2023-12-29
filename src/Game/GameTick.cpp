#include "Game/Game.h"

void Game::initTimer() {
    if (timer != nullptr) delete timer;
    timer = new Timer(nullptr, 1000 / GLOBAL_TICK);
    tick = 0;
}

void Game::slot_globalUpdate() {
    ++tick;
    core->update(tick);
    gui->update(tick);
}

int Game::getTick() const {
    return tick;
}
