#pragma once

// ゲーム全体を統括するクラス
class Game
{
public:
    Game();
    
    // ゲーム実行
    void Run();

private:
    // 初期化処理
    void Initialize();
};
