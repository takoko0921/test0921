#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER

//******************************************************************************
//
//
//      Player.h
//
//
//******************************************************************************

//==============================================================================
//
//      移動アルゴリズム
//
//==============================================================================

// プレイヤー操作クラス
class Player : public MoveAlg
{
	void gravity(OBJ2D* obj);
	void againstWall(OBJ2D* obj);
	void againstMapChip(OBJ2D* obj);
	void areaCheck(OBJ2D* obj);
	void deceleration(OBJ2D* obj);


public:
	// 定数（これらはこの関数内でしか使用しないため、ここで宣言している）
	static constexpr float KASOKU = 0.2f;     // 横方向・縦方向の加速度
	static constexpr float SPEED_MAX_Y = 7.0f;     // 最大の落下速度


    void move(OBJ2D* obj);


};

// 移動アルゴリズムの実体
EXTERN Player player;


// 消去アルゴリズム
class ErasePlayer : public EraseAlg
{
    void erase(OBJ2D* obj);
};

// 消去アルゴリズムの実体
EXTERN ErasePlayer      erasePlayer;

class PlayerManager : public OBJ2DManager
{
public:
};


#endif // !INCLUDED_PLAYER
