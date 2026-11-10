#pragma once

#include "GameModel.h"
#include "GameView.h"

// ゲーム制御フローを担当する Controller クラス
class GameController
{
public:
    GameController();

    // メインループ実行
    void Run();

private:
    GameModel model;
    GameView view;

    // 各ゲーム状態処理
    void HandleTitle();
    void HandleBattle();
    void HandleMapClear();
    void HandleVictory();
    void HandleGameOver();

    // ヘルパーメソッド
    void CreateNextEnemy();
    int GetUserInput() const;
};