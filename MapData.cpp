
#include "MapData.h"

namespace
{
    const MapData mapTable[] =
    {
        {
            "マップ1：草原",
            3,  // 敵の数
            1,  // EXP倍率
            1,  // ゴールド倍率
            { EnemyType::Slime, EnemyType::Goblin }
        },
        {
            "マップ2：洞窟",
            5,
            2,
            2,
            { EnemyType::Goblin, EnemyType::Dragon }
        },
        {
            "マップ3：ドラゴンの巣",
            8,
            3,
            3,
            { EnemyType::Goblin, EnemyType::Dragon }
        }
    };
}

const MapData& GetMapData(int mapIndex)
{
    const int mapCount = GetMapCount();

    if (mapIndex < 0)
        mapIndex = 0;

    if (mapIndex >= mapCount)
        mapIndex = mapCount - 1;

    return mapTable[mapIndex];
}

int GetMapCount()
{
    return static_cast<int>(
        sizeof(mapTable) / sizeof(mapTable[0])
        );
}
