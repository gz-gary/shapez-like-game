#ifndef __MAP_H__
#define __MAP_H__

#include "common.h"
#include <stack>
#include "Core/CoreComponent.h"
#include "Core/Map/Block/Block.h"
#include "Core/Map/MineObject/MineObject.h"

#define for_in_map(iter, cond) for (auto &row : blk_mat) for (auto iter : row) if ((cond))

class Map : public CoreComponent {

    Q_OBJECT;

public:
    Map(CoreAdapter *_adapter);
    Map(Map &&) = default;
    Map(const Map &) = default;
    Map &operator=(Map &&) = default;
    Map &operator=(const Map &) = default;
    ~Map();

    /* load and save */
    void load(const char *path);
    void save(const char *path);

    void update(const int &tick);

    /* utility, frequently called operation */
    void setBlock(int x, int y, Block::BlockBase *blk);
    void removeBlock(int x, int y);
    Block::BlockBase* getBlock(int x, int y);
    void setDevice(int x, int y, std::string info);
    Block::MineBase* generateMine(int x, int y, Block::MineType type);
    Block::MineBase* generateMine(int x, int y, Block::MineBase* ref_mine);
    bool isBlockEmpty(int x, int y);
    bool isBlockEmpty(Block::BlockBase* blk);

    /* mission */
    int expandCenter();
    void expandMine();
    void expandMap();
    void upgradeDevice(int x, int y);

    /* to draw and place virtual pipe */
    void drawPipeLis(std::stack<std::pair<int, int>> p);
    void confirmVirt();

private:
    int width, height;
    int size_center;
    int x_center, y_center;
    Block::BlockBase *blk_mat[MAXN][MAXN];
    std::stack<PipeLisObj> virt_pipe_buffer;
    
};

#endif
