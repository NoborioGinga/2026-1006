#include "ObjectPool.h"

ObjectPool::ObjectPool()
{
    Reset();
}

Enemy* ObjectPool::GetEnemy()
{
    for (int i = 0; i < POOL_SIZE; i++)
    {
        if (!enemies[i].IsActive())
        {
            return &enemies[i];
        }
    }

    return nullptr;
}

void ObjectPool::ReleaseEnemy(Enemy* enemy)
{
    if (enemy != nullptr)
    {
        enemy->Reset();
    }
}

void ObjectPool::Reset()
{
    for (int i = 0; i < POOL_SIZE; i++)
    {
        enemies[i].Reset();
    }
}