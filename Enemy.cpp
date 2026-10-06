#include "Enemy.h"
#include <iostream>

Enemy::Enemy()
{
    name = "";
    hp = 0;
    maxHp = 0;
    attack = 0;
    gold = 0;
    exp = 0;
    active = false;
}

void Enemy::Initialize(const EnemyData& data)
{
    name = data.name;
    maxHp = data.maxHp;
    hp = maxHp;
    attack = data.attack;
    exp = data.exp;
    gold = data.gold;
    active = true;
}

void Enemy::TakeDamage(int damage)
{
    hp -= damage;

    if (hp < 0)
    {
        hp = 0;
    }
}



void Enemy::Reset()
{
    name = "";
    hp = 0;
    maxHp = 0;
    attack = 0;
    gold = 0;
    exp = 0;

    active = false;
}

bool Enemy::IsActive() const
{
    return active;
}

bool Enemy::IsDead() const
{
    return hp <= 0;
}

const char* Enemy::GetName() const
{
    return name;
}

int Enemy::GetHP() const
{
    return hp;
}

int Enemy::GetMaxHP() const
{
    return maxHp;
}

int Enemy::GetAttack() const
{
    return attack;
}

int Enemy::GetExp()const
{
    return exp;
}

int Enemy::GetGold()const
{
    return gold;

}