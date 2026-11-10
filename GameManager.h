#pragma once

// ゲームの状態定義
enum class GameState
{
    Title,      // タイトル画面
    Battle,     // バトル画面
    MapClear,   // マップクリア画面
    Victory,    // ビクトリー画面
    GameOver,   // ゲームオーバー画面
    Exit        // ゲーム終了
};

// ゲーム全体の状態を管理するシングルトン
class GameManager
{
public:
    // シングルトンインスタンス取得
    static GameManager& GetInstance();

    // 状態取得・設定
    GameState GetState() const;
    void SetState(GameState state);

    // ゲーム状態リセット
    void Reset();

    // 敵討伐数加算
    void AddDefeatedEnemy();
    int GetTotalDefeatedEnemies() const;

private:
    GameManager() = default;

    GameState currentState = GameState::Title;
    int totalDefeatedEnemies = 0;
};