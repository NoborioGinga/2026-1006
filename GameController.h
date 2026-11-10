#pragma once

#include "GameModel.h"
#include "GameView.h"
#include "GameManager.h"

// ゲーム制御を担当する Controller クラス
class GameController
{
public:
    GameController();
    void Run();

private:
    GameModel model;
    GameView view;

    // 各ゲーム状態の処理
    void HandleTitle();
    void HandleBattle();
    void HandleMapClear();
    void HandleVictory();
    void HandleGameOver();
    void CreateNextEnemy();
    int GetUserInput() const;
};