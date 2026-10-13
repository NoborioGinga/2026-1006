#pragma once

#include "EnemyData.h"
#include <vector>

struct MapData
{
    const char* name;
    int enemyCount;
    int expMultiplier;
    int goldMultiplier;
    std::vector<EnemyType> enemyTypes;
};

// マップ設定を取得する
const MapData& GetMapData(int mapIndex);

// マップの総数を取得する
int GetMapCount();
