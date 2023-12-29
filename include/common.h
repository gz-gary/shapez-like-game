#ifndef __COMMON_H__
#define __COMMON_H__

#define GLOBAL_TICK 30

#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "Core/Map/Block/Direction.h"

#include <QObject>

#define qcast(a, b) qobject_cast<b>((a))

#define MAXN 200
#define PI 3.1415926

enum class Info {
    Error_NotEmpty,
    Error_MinerOnMine,
    Error_RemoveMine,
    Error_RemoveCenter,
    Error_NoUpgradeChance,
    Error_NotUpgradable,
    Error_NoSpaceToExpandCenter,
    Error_NoEnoughMoney,
    Info_ExpandCenter,
    Info_Mission1Complete,
    Info_Mission2Complete,
    Info_Mission3Complete,
    Info_Mission4Complete,
    Info_UpgradePipe,
    Info_UpgradeMiner,
    Info_UpgradeCutter,
    Info_ExpandMap,
};

#endif
