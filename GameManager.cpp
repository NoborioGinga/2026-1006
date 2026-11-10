#include "GameManager.h"

// シングルトンインスタンス取得
GameManager& GameManager::GetInstance()
{
    static GameManager instance;
    return instance;
}

// 現在の状態取得
GameState GameManager::GetState() const
{
    return currentState;
}

// 状態設定
void GameManager::SetState(GameState state)
{
    currentState = state;
}

// ゲーム状態リセット
void GameManager::Reset()
{
    currentState = GameState::Title;
    totalDefeatedEnemies = 0;
}

// 敵討伐数加算
void GameManager::AddDefeatedEnemy()
{
    totalDefeatedEnemies++;
}

// 敵討伐数取得
int GameManager::GetTotalDefeatedEnemies() const
{
    return totalDefeatedEnemies;
}