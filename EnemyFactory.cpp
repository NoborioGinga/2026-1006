#include "EnemyFactory.h"

void EnemyFactory::CreateEnemy(Enemy& enemy, EnemyType type)
{
    EnemyData data;

    switch (type)
    {
	// 敵の種類に応じてデータを設定
	// スライム
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
        
    // ゴブリン
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

    // 魔女
    case EnemyType::Witch:

        data =
        {
            "魔女",
            60,
            20,
            150,
            100
        };

        break;

         // スケルトン    
	case EnemyType::Skeleton:
        data =
        {
            "スケルトン",
            70,
            16,
            110,
            60
        };
		break;


		// ゴーレム
        case EnemyType::Golem:
        data =
        {
            "ゴーレム",
            80,
            18,
            120,
            80
		};
        		break;

		// ドラゴン
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

    default: data =
    {
        "スライム",
        30,
        8,
        50,
        25
    };


        break;
    }

    enemy.Initialize(data);
}