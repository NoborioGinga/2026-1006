#pragma once

enum class EnemyType
{
	Slime,  // スライム
    Goblin, // ゴブリン
    Golem,  // ゴーレム
    Skeleton, // スケルトン
	Witch,   // 魔女     
    Dragon, // ドラゴン
};

struct EnemyData
{
    const char* name;

    int maxHp;
    int attack;
    int gold;
    int exp;
};