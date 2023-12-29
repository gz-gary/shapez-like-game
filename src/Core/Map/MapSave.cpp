#include "Core/Map/Map.h"
#include "Core/Core.h"
#include <fstream>
#include <sstream>
using namespace Block;
using namespace MineObject;

void Map::load(const char *path) {
    Pipe::glb_grade = 1;
    Cutter::glb_grade = 1;
    Miner::glb_grade = 1;

    size_center = 0;
    x_center = y_center = (1 << 20);
    std::ifstream in_file(path, std::ios::in);
    char buffer[1024];
    in_file.getline(buffer, 1024);
    while (strcmp(buffer, "Size")) in_file.getline(buffer, 1024);
    in_file >> width >> height;
    adapter->Map_changeMapSize(width, height);

    memset(blk_mat, 0, sizeof(blk_mat));
    for (int i = 1; i <= width; ++i)
        for (int j = 1; j <= height; ++j) {
            blk_mat[i][j] = new Empty(i, j, adapter);
            adapter->Map_setBlock(i, j, blk_mat[i][j]->getSymbStr());
        }

    for (int i = 1; i <= width; ++i)
        for (int j = 1; j <= height; ++j)
            for (int k = 0; k < 4; ++k)
                blk_mat[i][j]->neighbor[k] = getBlock(i + DIR_OFF[k][0], j + DIR_OFF[k][1]);


    in_file.getline(buffer, 1024);
    while (strcmp(buffer, "Block")) in_file.getline(buffer, 1024);
    int x, y, cnt;
    std::string type, dir1, dir2, src;
    in_file >> x >> y >> type;
    while (!in_file.fail())
    {
        DeviceBase *dvc = nullptr;
        if (type == "Miner")
        {
            in_file >> src;
            in_file >> dir1;

            Miner *ptr = new Miner(x, y, Direction(dir1), adapter);
            dvc = ptr;
            if (src == "Mine1") {
                Mine1 *mptr = new Mine1(x, y, adapter);
                adapter->Map_setBlock(x, y, mptr->getSymbStr());
                ptr->src = mptr;
            }
            else if (src == "Mine2") {
                Mine2 *mptr = new Mine2(x, y, adapter);
                adapter->Map_setBlock(x, y, mptr->getSymbStr());
                ptr->src = mptr;
            }
            setBlock(x, y, ptr);
        }
        else if (type == "Pipe") {
            in_file >> dir1 >> dir2;
            Pipe *ptr = new Pipe(x, y, Direction(dir1), Direction(dir2), adapter);
            dvc = ptr;
            setBlock(x, y, ptr);
        }
        else if (type == "Trashbin") {
            Trashbin *ptr = new Trashbin(x, y, adapter);
            dvc = ptr;
            setBlock(x, y, ptr);
        }
        else if (type == "Center") {
            Center *ptr = new Center(x, y, adapter);
            dvc = ptr;
            ++size_center;
            if (x < x_center) x_center = x;
            if (y < y_center) y_center = y;
            setBlock(x, y, ptr);
        }
        else if (type == "Mine1") {
            Mine1 *ptr = new Mine1(x, y, adapter);
            setBlock(x, y, ptr);
        }
        else if (type == "Mine2") {
            Mine2 *ptr = new Mine2(x, y, adapter);
            setBlock(x, y, ptr);
        }
        else if (type == "Rotater") {
            int alt;
            in_file >> alt;
            in_file >> dir1;
            Rotater *ptr = new Rotater(x, y, Direction(dir1), alt, adapter);
            dvc = ptr;
            setBlock(x, y, ptr);
        }
        else if (type == "Cutter") {
            int alt;
            in_file >> alt;
            in_file >> dir1;
            if (alt == 0)
            {
                Direction dir(dir1), dir1 = dir.reverse(), dir2 = dir1.rotate();
                Cutter *c0 = new Cutter(x, y, dir1, dir, 0, adapter);
                int x1 = x + DIR_OFF[dir2][0], y1 = y + DIR_OFF[dir2][1];
                Cutter *c1 = new Cutter(x1, y1, Direction::None, dir, 1, adapter);
                c0->couple = c1;
                c1->couple = c0;

                setBlock(x, y, c0);
                setBlock(x1, y1, c1);
                dvc = c0;
            }
            else
                dvc = qobject_cast<DeviceBase *>(getBlock(x, y));
        }
        if (dvc != nullptr)
        {
            in_file >> cnt;
            MineObjectBase *obj;
            for (int i = 1, tp, pos; i <= cnt; ++i)
            {
                in_file >> tp >> pos;
                if (tp == 1) obj = new MineObject1(adapter);
                else if (tp == 2) obj = new MineObject2(adapter);
                else if (tp == 21) obj = new MineObject21(adapter);
                else if (tp == 22) obj = new MineObject22(adapter);
                obj->pos = pos;
                dvc->append(obj);
                adapter->All_newMineObj(obj->id, obj->getSymbStr());
            }
            dvc->handleObj(0);
        }
        in_file >> x >> y >> type;
    }
    in_file.close();

    size_center = sqrt(size_center);
}

void Map::setDevice(int x, int y, std::string info) {
    std::istringstream in_str(info);
    std::string type, dir1, dir2;
    in_str >> type;
    auto blk = getBlock(x, y);
    if (blk == nullptr) return;
    if (type == "Miner")
    {
        if (!qcast(blk, Block::MineBase*)) {
            adapter->All_raiseInfo(Info::Error_MinerOnMine);
            return;
        }
        //in_str >> src;
        in_str >> dir1;

        auto mptr = qobject_cast<MineBase*>(getBlock(x, y));
        Miner *ptr = new Miner(x, y, Direction(dir1), adapter);
        ptr->src = mptr;
        blk_mat[x][y] = nullptr;
        setBlock(x, y, ptr);
    }
    else {
        if (type == "Confirm") {
            confirmVirt();
        }
        else if (type == "Remove") {
            removeBlock(x, y);
        }
        else if (type == "Upgrade") {
            upgradeDevice(x, y);
        } else {
            if (!isBlockEmpty(x, y)) {
                adapter->All_raiseInfo(Info::Error_NotEmpty);
                return;
            }
            if (type == "Pipe") {
                in_str >> dir1 >> dir2;
                Pipe *ptr = new Pipe(x, y, Direction(dir1), Direction(dir2), adapter);
                setBlock(x, y, ptr);
            }
            else if (type == "Trashbin") {
                Trashbin *ptr = new Trashbin(x, y, adapter);
                setBlock(x, y, ptr);
            }
            else if (type == "Cutter") {
                int alt;
                in_str >> alt;
                in_str >> dir1;
                if (alt == 0)
                {
                    Direction dir(dir1), dir1 = dir.reverse(), dir2 = dir1.rotate();
                    int x1 = x + DIR_OFF[dir2][0], y1 = y + DIR_OFF[dir2][1];
                    auto blk2 = getBlock(x1, y1);
                    if (!isBlockEmpty(blk2)) {
                        adapter->All_raiseInfo(Info::Error_NotEmpty);
                        return;
                    }
                    Cutter *c0 = new Cutter(x, y, dir1, dir, 0, adapter);
                    Cutter *c1 = new Cutter(x1, y1, Direction::None, dir, 1, adapter);
                    c0->couple = c1;
                    c1->couple = c0;

                    setBlock(x, y, c0);
                    setBlock(x1, y1, c1);
                }
            }
            else if (type == "Rotater") {
                int alt;
                in_str >> alt;
                in_str >> dir1;
                Direction d_to(dir1);
                auto rot = new Rotater(x, y, Direction(dir1), alt, adapter);
                setBlock(x, y, rot);
            }
        }
        
   }
}

void Map::save(const char *path) {
    std::ofstream out_file(path, std::ios::out);
    out_file << "Size" << std::endl;
    out_file << width << " " << height << std::endl;

    out_file << "Block" << std::endl;

    for_in_map(blk, qcast(blk, Block::DeviceBase*)) {
        auto dvc = qcast(blk, Block::DeviceBase*);
        auto cutter = qcast(dvc, Block::Cutter*);
        auto pipe = qcast(dvc, Block::Pipe*);
        auto trashbin = qcast(dvc, Block::Trashbin*);
        auto center = qcast(dvc, Block::Center*);
        auto miner = qcast(dvc, Block::Miner*);
        auto rotater = qcast(dvc, Block::Rotater*);
        if (cutter)
        {
            if (!cutter->alt) {
                auto couple = cutter->couple;
                out_file << cutter->x << " " << cutter->y << " ";
                out_file << "Cutter " << 0 << " " << cutter->dir_to.getStr() << " ";
                out_file << cutter->obj_lis.size() << std::endl;
                for (auto iter = cutter->obj_lis.begin(); iter != cutter->obj_lis.end(); ++iter)
                    out_file << (*iter)->getTypeStr() << " " << (*iter)->pos << std::endl;
                out_file << couple->x << " " << couple->y << " ";
                out_file << "Cutter " << 1 << " " << cutter->dir_to.getStr() << " ";
                out_file << couple->obj_lis.size() << std::endl;
                for (auto iter = couple->obj_lis.begin(); iter != couple->obj_lis.end(); ++iter)
                    out_file << (*iter)->getTypeStr() << " " << (*iter)->pos << std::endl;
            }
            continue;
        }
        out_file << dvc->x << " " << dvc->y << " ";
        if (pipe)
            out_file << "Pipe " << pipe->dir_frm.getStr() << " " << pipe->dir_to.getStr() << " ";
        else if (trashbin)
            out_file << "Trashbin ";
        else if (center)
            out_file << "Center ";
        else if (miner)
            out_file << "Miner " << miner->src->getSymbStr() << " " << miner->dir_to.getStr() << " ";
        else if (rotater)
            out_file << "Rotater " << rotater->alt << " " << rotater->dir_to.getStr() << " ";
        out_file << dvc->obj_lis.size() << std::endl;
        for (auto iter = dvc->obj_lis.begin(); iter != dvc->obj_lis.end(); ++iter)
            out_file << (*iter)->getTypeStr() << " " << (*iter)->pos << std::endl;
    }
    for_in_map(blk, qcast(blk, Block::MineBase*)) {
        auto mine = qcast(blk, Block::MineBase*);
        out_file << blk->x << " " << blk->y << " ";
        out_file << mine->getSymbStr() << std::endl;
    }

}
