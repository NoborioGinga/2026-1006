#include "Player.h"
#include <iostream>

// コンストラクタ
Player::Player()
{
    maxHp = 100;
    hp = maxHp;
    attack = 20;
    exp = 0;
    gold = 0;
}

void Player::Attack()
{
    std::cout << "プレイヤーの攻撃！" << std::endl;
}

void Player::TakeDamage(int damage)
{
    hp -= damage;

    if (hp < 0)
    {
        hp = 0;
    }
}

void Player::Heal(int amount)
{
    hp += amount;

    if (hp > maxHp)
    {
        hp = maxHp;
    }
}

bool Player::IsDead() const
{
    return hp <= 0;
}

int Player::GetHP() const
{
    return hp;
}

int Player::GetMaxHP() const
{
    return maxHp;
}

int Player::GetAttack() const
{
    return attack;
}

int Player::GetExp()const
{
    return exp;
}

int Player::GetGold()const
{
    return gold;

}