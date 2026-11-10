#include "Game.h"
#include "GameController.h"
#include "GameManager.h"

// コンストラクタ
Game::Game()
{
    Initialize();
}

// 初期化処理
void Game::Initialize()
{
    // GameManager をシングルトンで初期化
    GameManager::GetInstance();
}

// ゲーム実行（MVC Controller 使用）
void Game::Run()
{
    // GameController が全フロー制御を担当
    GameController controller;
    controller.Run();
}
