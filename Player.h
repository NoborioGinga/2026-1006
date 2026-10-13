#pragma once

class Player
{
public:
    Player();
    

    void Attack();

    void TakeDamage(int damage);

    void Heal(int amount);

	void AddExp(int amount);

	void AddGold(int amount);

    bool IsDead() const;

    int GetHP() const;
    int GetMaxHP() const;
    int GetAttack() const;
    int GetExp() const;
    int GetGold() const;
	//レベルアップ機能を追加
	int GetLevel() const;
    int GetNextLevelExp() const;

private:
    int hp;
    int maxHp;
    int attack;
    int exp;
    int gold;
    int level;
    int nextLevelExp;
};