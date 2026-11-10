#pragma once

// プレイヤーの状態とロジックを管理する Model クラス
class Player
{
public:
    Player();

    // 攻撃・ダメージ処理
    void Attack();
    void TakeDamage(int damage);
    void Heal(int amount);

    // EXP・ゴールド管理
    void AddExp(int amount);
    void AddGold(int amount);

    // 状態確認
    bool IsDead() const;
    bool IsLeveledUp() const;

    // ステータス取得
    int GetHP() const;
    int GetMaxHP() const;
    int GetAttack() const;
    int GetExp() const;
    int GetGold() const;
    int GetLevel() const;
    int GetNextLevelExp() const;

    // レベルアップフラグをリセット
    void ResetLevelUpFlag();

private:
    int hp;
    int maxHp;
    int attack;
    int exp;
    int gold;
    int level;
    int nextLevelExp;
    bool leveledUp;  // レベルアップしたかのフラグ

    // レベルアップ処理（内部用）
    void LevelUp();
};