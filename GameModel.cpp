#include "GameModel.h"
#include "MapData.h"

// コンストラクタ
GameModel::GameModel()
    : currentEnemy(nullptr), currentMap(0), defeatedOnMap(0)
{
}

// プレイヤー取得（参照型）
Player& GameModel::GetPlayer()
{
    return player;
}

// プレイヤー取得（const）
const Player& GameModel::GetPlayer() const
{
    return player;
}

// 現在の敵取得
Enemy* GameModel::GetCurrentEnemy() const
{
    return currentEnemy;
}

// 現在のマップ取得
int GameModel::GetCurrentMap() const
{
    return currentMap;
}

// 倒した敵数取得
int GameModel::GetDefeatedOnMap() const
{
    return defeatedOnMap;
}

// 敵プール取得
ObjectPool& GameModel::GetEnemyPool()
{
    return enemyPool;
}

// 敵設定
void GameModel::SetCurrentEnemy(Enemy* enemy)
{
    currentEnemy = enemy;
}

// マップ設定
void GameModel::SetCurrentMap(int map)
{
    currentMap = map;
}

// 倒した敵数設定
void GameModel::SetDefeatedOnMap(int count)
{
    defeatedOnMap = count;
}

// 倒した敵数インクリメント
void GameModel::IncrementDefeatedOnMap()
{
    defeatedOnMap++;
}

// ゲーム状態リセット
void GameModel::ResetGameState()
{
    player = Player();
    enemyPool.Reset();
    currentEnemy = nullptr;
    currentMap = 0;
    defeatedOnMap = 0;
}

// プレイヤー攻撃実行
void GameModel::ExecutePlayerAttack(int& outDamage)
{
    player.Attack();
    outDamage = player.GetAttack();
    
    if (currentEnemy != nullptr)
    {
        currentEnemy->TakeDamage(outDamage);
    }
}

// 敵の反撃実行
void GameModel::ExecuteEnemyAttack(int& outDamage)
{
    if (currentEnemy != nullptr)
    {
        outDamage = currentEnemy->GetAttack();
        player.TakeDamage(outDamage);
    }
}

// プレイヤー回復実行
void GameModel::ExecutePlayerHeal(int healAmount)
{
    player.Heal(healAmount);
}

// 敵撃破処理
void GameModel::HandleEnemyDefeated(int& outExp, int& outGold)
{
    if (currentEnemy != nullptr)
    {
        const MapData& map = GetMapData(currentMap);
        
        // 報酬計算
        outExp = currentEnemy->GetExp() * map.expMultiplier;
        outGold = currentEnemy->GetGold() * map.goldMultiplier;
        
        // プレイヤーに報酬付与
        player.AddExp(outExp);
        player.AddGold(outGold);
    }
}