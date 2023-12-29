#ifndef __CORE_H__
#define __CORE_H__

#include "common.h"
#include "Core/CoreAdapter.h"
#include "Core/Map/Map.h"

class Core {

    friend class Game;
    friend class Map;
    friend class CoreAdapter;

public:
    Core();
    Core(Core &&) = default;
    Core(const Core &) = default;
    Core &operator=(Core &&) = default;
    Core &operator=(const Core &) = default;
    ~Core();

    void load(const char *path_savefile);
    void save(const char *path_savefile);
    void reload(const char *path_savefile);
    void update(const int &_tick);
    void sellAll();
    void increaseRate();
    int getTick() const;
    void func();

private:
    CoreAdapter *adapter;
    Map *map;
    int tick;
    int cnt_obj1, cnt_obj2, cnt_obj21, cnt_obj22;
    int total_cnt_obj1, total_cnt_obj2, total_cnt_obj21, total_cnt_obj22, total_cnt_obj22_rot;
    int money;
    int lvup;
    float epnt, rate;
    
};

#endif
