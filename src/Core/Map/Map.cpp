#include "Core/Map/Map.h"
using namespace Block;

Map::Map(CoreAdapter *_adapter) :
    CoreComponent(_adapter)
{ }

Map::~Map() {
    for (auto &row : blk_mat) for (auto blk : row) {
        delete blk;
    }
}

void Map::update(const int &tick) {
    DirectedDeviceBase *ddvc;
    DeviceBase *dvc;

    /* reset flag for recursive call of delivery */
    for_in_map(blk, dvc = qcast(blk, Block::DeviceBase*)) {
        /* for each device in the map */
        dvc->resetDelivery();
    }

    for_in_map(blk, ddvc = qcast(blk, Block::DirectedDeviceBase*)) {
        /* for each directed device (only these devices can deliver object) */
        ddvc->deliverObj();
    }

    for_in_map(blk, dvc = qcast(blk, Block::DeviceBase*)) {
        /* for each device, handle their objects in their own ways */
        dvc->handleObj(tick);
    }
}

BlockBase* Map::getBlock(int x, int y)
{
    if (x >= 1 && x <= width && y >= 1 && y <= height) return blk_mat[x][y];
    else return nullptr;
}

void Map::setBlock(int x, int y, BlockBase *blk)
{
    if (blk_mat[x][y] != nullptr) delete blk_mat[x][y];
    BlockBase *ptr;
    for (int k = 0, l; k < 4; ++k) // set new neighbour
    {
        l = (k + 2) % 4;
        ptr = getBlock(x + DIR_OFF[k][0], y + DIR_OFF[k][1]);
        blk->neighbor[k] = ptr;
        if (ptr != nullptr) ptr->neighbor[l] = blk;
    }
    blk_mat[x][y] = blk;
    adapter->Map_setBlock(x, y, blk->getSymbStr());

}

void Map::removeBlock(int x, int y) {
    auto blk = getBlock(x, y);
    if (qcast(blk, Block::Miner*))
    {
        Miner *miner = qcast(blk, Block::Miner*);

        /* set the block to the miner's source mine (fake remove) */
        setBlock(x, y, miner->src);
    }
    else if (qcast(blk, Block::Cutter*))
    {
        Cutter *cutter = qcast(blk, Block::Cutter*),
               *cutter_main, *cutter_vice;
        if (cutter->alt == 0)
            cutter_main = cutter, cutter_vice = cutter->couple;
        else
            cutter_vice = cutter, cutter_main = cutter->couple;

        /* remove both the main and the vice cutter */
        setBlock(cutter_main->x, cutter_main->y, new Empty(cutter_main->x, cutter_main->y, adapter));
        setBlock(cutter_vice->x, cutter_vice->y, new Empty(cutter_vice->x, cutter_vice->y, adapter));
    }
    else if (qcast(blk, Block::MineBase*)) {
        //adapter->All_raiseInfo(Info::Error_RemoveMine);
        return;
    }
    else if (qcast(blk, Block::Center*)) {
        // could not remove the center
        //adapter->All_raiseInfo(Info::Error_RemoveCenter);
    }
    else setBlock(x, y, new Empty(x, y, adapter)); // it's a pipe, directly remove
}

bool Map::isBlockEmpty(int x, int y) {
    auto blk = getBlock(x, y);
    return qcast(blk, Block::Empty*) != nullptr;
}

bool Map::isBlockEmpty(Block::BlockBase* blk) {
    return qcast(blk, Block::Empty*) != nullptr;
}

Block::MineBase* Map::generateMine(int x, int y, Block::MineType type) {
    switch (type) {
    case MineType::Mine1:
        return new Mine1(x, y, adapter);
    case MineType::Mine2:
        return new Mine2(x, y, adapter);
    }
}

Block::MineBase* Map::generateMine(int x, int y, Block::MineBase* ref_mine) {
    return generateMine(x, y, ref_mine->getType());
}

