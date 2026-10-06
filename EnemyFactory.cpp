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
            8
        };

        break;

    case EnemyType::Goblin:

        data =
        {
            "ゴブリン",
            50,
            12
        };

        break;

    case EnemyType::Dragon:

        data =
        {
            "ドラゴン",
            100,
            20
        };

        break;
    }

    enemy.Initialize(data);
}