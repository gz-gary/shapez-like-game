#include "Core/Core.h"
#include <fstream>

void Core::load(const char *path_savefile) {
    map = new Map(adapter);
    map->load(path_savefile);

    std::ifstream in_file(path_savefile, std::ios::in);
    char buffer[1024];
    in_file.getline(buffer, 1024);
    while (strcmp(buffer, "Data"))
        in_file.getline(buffer, 1024);
    in_file >> money >> cnt_obj1 >> cnt_obj2 >> cnt_obj21 >> cnt_obj22 >> lvup >> epnt;
    total_cnt_obj1 = 0;
    total_cnt_obj2 = 0;
    total_cnt_obj21 = 0;
    total_cnt_obj22 = 0;
    total_cnt_obj22_rot = 0;
    rate = 3 - 2 * exp(-epnt);
    adapter->Core_changeMoney(money);
    adapter->Center_changeObjCnt(1, 0);
    adapter->Center_changeObjCnt(2, 0);
    adapter->Center_changeObjCnt(21, 0);
    adapter->Center_changeObjCnt(22, 0);
    adapter->All_changeLvup(lvup);
    adapter->changeRate(rate);

    in_file.close();

    //printf("%s\n", path_savefile);
}

void Core::save(const char *path_savefile) {
    map->save(path_savefile);

    std::ofstream out_file(path_savefile, std::ios::app);
    char buffer[64];
    sprintf(buffer, "%.1lf", epnt);

    out_file << "Data" << std::endl;
    out_file << money << std::endl;
    out_file << cnt_obj1 << std::endl;
    out_file << cnt_obj2 << std::endl;
    out_file << cnt_obj21 << std::endl;
    out_file << cnt_obj22 << std::endl;
    out_file << lvup << std::endl;
    out_file << buffer << std::endl;
}

void Core::reload(const char *path_savefile) {
    delete map;
    load(path_savefile);
}
