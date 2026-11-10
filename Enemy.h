#pragma once

#include "EnemyData.h"
#include <string>

// 敵の状態とロジックを管理する Model クラス
class Enemy
{
public:
    Enemy();

    // 敵を初期化（敵タイプデータで）
    void Initialize(const EnemyData& data);

    // ダメージを受ける
    void TakeDamage(int damage);

    // 敵の状態をリセット
    void Reset();

    // 状態確認メソッド
    bool IsActive() const;
    bool IsDead() const;

    // ステータス取得
    const char* GetName() const;  // const char* を返す
    int GetHP() const;
    int GetMaxHP() const;
    int GetAttack() const;
    int GetGold() const;
    int GetExp() const;

private:
    std::string name;  // std::string で管理
    int hp;
    int maxHp;
    int attack;
    int exp;
    int gold;
    bool active;
};