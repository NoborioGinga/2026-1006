#pragma once

class Player
{
public:
    Player();

    void Attack();

    void TakeDamage(int damage);

    void Heal(int amount);

    bool IsDead() const;

    int GetHP() const;
    int GetMaxHP() const;
    int GetAttack() const;

private:
    int hp;
    int maxHp;
    int attack;
};