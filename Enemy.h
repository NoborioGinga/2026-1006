#pragma once

#include "EnemyData.h"

class Enemy
{
public:
    Enemy();

    void Initialize(const EnemyData& data);

    void TakeDamage(int damage);

   

    void Reset();

    bool IsActive() const;

    bool IsDead() const;

    const char* GetName() const;

    int GetHP() const;

    int GetMaxHP() const;

    int GetAttack() const;

private:
    const char* name;

    int hp;
    int maxHp;
    int attack;

    bool active;
};