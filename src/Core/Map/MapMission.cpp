#include "Core/Core.h"
#include "Core/CoreAdapter.h"
#include "Core/Map/Map.h"
#include "Core/Map/Block/Direction.h"
#include <vector>

using std::pair;
using std::vector;
using namespace Block;

int Map::expandCenter() {
    vector<pair<int, int>> vec; // store the block to check
    for (int j = 0; j <= size_center; ++j) vec.push_back({x_center + size_center, y_center + j});
    for (int i = 0; i <= size_center; ++i) vec.push_back({x_center + i, y_center + size_center});
    vec.push_back({x_center + size_center, y_center + size_center});
    for (auto v : vec)
        if (!isBlockEmpty(v.first, v.second)) {
            adapter->All_raiseInfo(Info::Error_NoSpaceToExpandCenter);
            return -1;
        }
    for (auto v : vec)
        setBlock(v.first, v.second, new Center(v.first, v.second, adapter));
    adapter->All_raiseInfo(Info::Info_ExpandCenter);
    ++size_center;
    return 0;
}

void Map::expandMine() {
    BlockBase *blk, *nbr;
    int id, x, y, type, flag;
    vector<pair<int, int>> vec; // store the block
    if (rand() & 1) // new mine block
    {
        for_in_map(blk_i, isBlockEmpty(blk_i)) // for all the empty block
            vec.push_back({blk_i->x, blk_i->y});
        id = rand() % vec.size(); // choose a random empty block to place new mine block
        x = vec[id].first, y = vec[id].second;
        type = rand() % 2; // random type of the new mine block
        setBlock(x, y, generateMine(x, y, (MineType)type));
    } else { // expand old mine blocks
        for_in_map(blk_i, qcast(blk_i, Block::MineBase*) || qcast(blk_i, Block::Miner*)) { // this block is a mine or a miner
            flag = 0;
            for (int k = 0; k < 4; ++k) // and it has empty neighbor
                if (isBlockEmpty(blk_i->neighbor[k])) {
                    flag = 1;
                    break;
                }
            if (flag)
                vec.push_back({blk_i->x, blk_i->y});
        }
        id = rand() % vec.size(); // random mine block to expand
        x = vec[id].first, y = vec[id].second;
        blk = getBlock(x, y);
        auto mine = qcast(blk, Block::MineBase*);
        if (!mine) mine = qcast(blk, Block::Miner*)->src;
        for (int k = 0; k < 4; ++k) {
            nbr = blk->neighbor[k];
            if (isBlockEmpty(nbr))
                setBlock(nbr->x, nbr->y, generateMine(nbr->x, nbr->y, mine));
        }
    }
}

void Map::expandMap() {
    int w = width + 5, h = height + 5;
    for (int i = 1; i <= w; ++i)
        for (int j = 1; j <= h; ++j)
            if (i > width || j > height)
                blk_mat[i][j] = new Empty(i, j, adapter);
    width = w, height = h;
    for (int i = 1; i <= w; ++i)
        for (int j = 1; j <= h; ++j)
            for (int k = 0; k < 4; ++k)
                blk_mat[i][j]->neighbor[k] = getBlock(i + DIR_OFF[k][0], j + DIR_OFF[k][1]);
    adapter->Map_changeMapSize(width, height);
    adapter->All_raiseInfo(Info::Info_ExpandMap);
}

void Map::upgradeDevice(int x, int y) {
    auto blk = getBlock(x, y);
    if (adapter->core->lvup <= 0) {
        adapter->All_raiseInfo(Info::Error_NoUpgradeChance);
        return;
    }
    if (qcast(blk, Block::Miner*)) {
        adapter->All_raiseInfo(Info::Info_UpgradeMiner);
        ++Block::Miner::glb_grade;
        for_in_map(blk_i, qcast(blk_i, Block::Miner*))
            qcast(blk_i, Block::DeviceBase*)->upgrade();
    } else if (qcast(blk, Block::Cutter*)) {
        adapter->All_raiseInfo(Info::Info_UpgradeCutter);
        ++Block::Cutter::glb_grade;
        for_in_map(blk_i, qcast(blk_i, Block::Cutter*))
            qcast(blk_i, Block::DeviceBase*)->upgrade();
    } else if (qcast(blk, Block::Pipe*)) {
        adapter->All_raiseInfo(Info::Info_UpgradePipe);
        ++Block::Pipe::glb_grade;
        for_in_map(blk_i, qcast(blk_i, Block::Pipe*))
            qcast(blk_i, Block::DeviceBase*)->upgrade();
    } else {
        adapter->All_raiseInfo(Info::Error_NotUpgradable);
        return;
    }
    --adapter->core->lvup;
    adapter->All_changeLvup(adapter->core->lvup);
}

