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
    level = 1;
    nextLevelExp = 100;
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


void Player::AddExp(int amount)
{
   if(amount<=0)
   {
       return;
   }

       exp += amount;

	   std::cout << "EXPを" << amount 
           << "獲得！" << std::endl;
	   // レベルアップ判定
       while (exp >= nextLevelExp) 
       {
           level++;

           // 最大HPを7上げる
           maxHp += 7;

           // 攻撃力を2上げる
           attack += 2;

           //HPを全回復
           hp = maxHp;
           std::cout << std::endl;
           std::cout << " レベルアップ！! " << std::endl;
           std::cout << "レベル：" << level << std::endl;
           std::cout << "最大HPが7上昇！" << std::endl;
           std::cout << "攻撃力が2上昇！" << std::endl;
           std::cout << "HPが全回復した！" << std::endl;

           // 次のレベルに必要な累積EXPを増やす
           nextLevelExp += 100 + (level - 2) * 50;
       }

}
 
void Player::AddGold(int amount)
{
    gold += amount;
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

// 次のレベルアップに必要な累積EXP取得

int Player::GetLevel() const
{
    return level;
}


int Player::GetNextLevelExp() const
{
    return nextLevelExp;
}