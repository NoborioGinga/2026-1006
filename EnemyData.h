#pragma once

enum class EnemyType
{
    Slime,
    Goblin,
    Golem,
    Skeleton,
    Witch,
    Dragon
};

struct EnemyData
{
    const char* name;  // これは const char* のポインタ（文字列リテラル）
    int maxHp;
    int attack;
    int exp;
    int gold;
};