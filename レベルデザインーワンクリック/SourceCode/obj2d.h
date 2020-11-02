#ifndef INCLUDED_OBJ2D
#define	INCLUDED_OBJ2D
//******************************************************************************
//
//
//      OBJ2Dクラス
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include <list>
#include "../GameLib/vector.h"
#include "../GameLib/obj2d_data.h"

// 前方宣言
class OBJ2D;

//==============================================================================

// 移動アルゴリズムクラス（抽象クラス）
class MoveAlg
{
public:
    virtual void move(OBJ2D* obj) = 0;  // 純粋仮想関数を持つので、MoveAlg型のオブジェクトは宣言できない（派生させて使う）
};

// 消去アルゴリズムクラス（抽象クラス）
class EraseAlg
{
public:
    virtual void erase(OBJ2D* obj) = 0; // 上と同様
};

//==============================================================================

//==============================================================================
//
//      OBJ2Dクラス
//
//==============================================================================

class OBJ2D
{
public:
    // メンバ変数
    GameLib::SpriteData*    data = nullptr;               // スプライトデータ									
	GameLib::Anime          anime = {};              // アニメーションクラス

	VECTOR2                 position = {};           // 位置
    VECTOR2                 scale = {};              // スケール
    float                   angle = 0;              // 角度
    VECTOR4                 color = {};              // 描画色
    VECTOR2                 size = {};               // あたり用サイズ（縦横）

    MoveAlg*                mvAlg = nullptr;               // 移動アルゴリズム
    EraseAlg*               eraseAlg = nullptr;           // 消去アルゴリズム

    float                   velocity = 0;           // 速度
    VECTOR2                 speed = {};              // 瞬間の移動量ベクトル
    int                     state = 0;              // ステート
    int                     timer = 0;              // タイマー

    GameLib::fRECT          hitRect = {};            // あたり判定RECT

    bool                    judgeFlg = false;          // あたり判定の有無（true:有り / false:無し）
    bool                    isDrawHitRect = false;      // あたり判定描画フラグ

    VECTOR2                 delta = {};              // 移動量の差分


	GameLib::AnimeData* animeData = nullptr;    // アニメーションデータ
	bool					onGround = false;

	bool					lHit = false;
	bool					rHit = false;
	bool					tHit = false;
	bool					bHit = false;


	

	int						stayCount = 0;

	bool					hitFlg = false;

	int						type = 0;
public:
    // メンバ関数
    OBJ2D();        // コンストラクタ
	void move();    // 移動
	void draw();    // 描画

	void drawHitRect(const VECTOR4&);           // 当たり判定描画

    bool animeUpdate();    // アニメーションのアップデート
};

//==============================================================================

// OBJ2DManagerクラス
class OBJ2DManager
{
protected:
    std::list<OBJ2D>  objList; // リスト（OBJ2Dの配列のようなもの）
public:
    // デストラクタ
    ~OBJ2DManager();

    void init();    // 初期化
    void update();  // 更新
    void draw();    // 描画

    OBJ2D* add(MoveAlg* mvAlg, const VECTOR2& pos = VECTOR2(0, 0)); // objListに新たなOBJ2Dを追加する

	OBJ2D* addSpr(int type,GameLib::SpriteData* data,MoveAlg* mvAlg, const VECTOR2& pos = VECTOR2(0, 0)); // objListに新たなOBJ2Dを追加する
    std::list<OBJ2D>* getList() { return &objList; }                // objListを取得する
};

//******************************************************************************

#endif// ! INCLUDED_OBJ2D