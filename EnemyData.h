#pragma once

enum class EnemyType
{
    Slime,
    Goblin,
    Dragon
};

struct EnemyData
{
    const char* name;

    int maxHp;
    int attack;
    int gold;
    int exp;
};