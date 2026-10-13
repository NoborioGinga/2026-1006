#pragma once

#include "Enemy.h"

class ObjectPool
{
public:
    static const int POOL_SIZE = 6;

    ObjectPool();

    Enemy* GetEnemy();

    void ReleaseEnemy(Enemy* enemy);

    void Reset();

private:
    Enemy enemies[POOL_SIZE];
};