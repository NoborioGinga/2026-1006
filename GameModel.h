#pragma once

#include "Player.h"
#include "Enemy.h"
#include "ObjectPool.h"
#include "MapData.h"

class GameModel
{
public:
    GameModel();

    // ゲーム状態の取得
    Player& GetPlayer();
    const Player& GetPlayer() const;
    Enemy* GetCurrentEnemy() const;
    int GetCurrentMap() const;
    int GetDefeatedOnMap() const;
    ObjectPool& GetEnemyPool();

    // ゲーム状態の更新
    void SetCurrentEnemy(Enemy* enemy);
    void SetCurrentMap(int map);
    void SetDefeatedOnMap(int count);
    void IncrementDefeatedOnMap();
    void ResetGameState();

    // バトルロジック
    void ExecutePlayerAttack(int& outDamage);
    void ExecuteEnemyAttack(int& outDamage);
    void ExecutePlayerHeal(int healAmount);
    void HandleEnemyDefeated(int& outExp, int& outGold);

private:
    Player player;
    ObjectPool enemyPool;
    Enemy* currentEnemy;
    int currentMap;
    int defeatedOnMap;
};