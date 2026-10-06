#pragma once

#include "Enemy.h"

class EnemyFactory
{
public:
    static void CreateEnemy(Enemy& enemy, EnemyType type);
};