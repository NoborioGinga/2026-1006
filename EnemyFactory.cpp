#include "EnemyFactory.h"

void EnemyFactory::CreateEnemy(Enemy& enemy, EnemyType type)
{
    EnemyData data;

    switch (type)
    {
    case EnemyType::Slime:

        data =
        {
            "スライム",
            30,
            8,
            50,
            25
        };

        break;

    case EnemyType::Goblin:

        data =
        {
            "ゴブリン",
            50,
            12,
            70,
            50
        };

        break;

    case EnemyType::Dragon:

        data =
        {
            "ドラゴン",
            100,
            20,
            150,
            100
        };

        break;
    }

    enemy.Initialize(data);
}