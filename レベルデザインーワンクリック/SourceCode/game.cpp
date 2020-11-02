//******************************************************************************
//
//
//      ゲーム
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< 変数 >----------------------------------------------------------------
Game Game::instance_;

//--------------------------------------------------------------
//  初期化処理
//--------------------------------------------------------------
void Game::init()
{
    Scene::init();	    // 基底クラスのinitを呼ぶ

    playerManager_      = new PlayerManager;
    bgManager_          = new BG;
	wallManager_		= new Wall;
	bottanManager_		= new MapObjManager;

	tutorail = new Tutorial;
		

    isPaused = false;   // ポーズフラグの初期化
}

//--------------------------------------------------------------
//  更新処理
//--------------------------------------------------------------
void Game::update()
{
    using namespace input;

    // ソフトリセット
    if ((STATE(0) & PAD_SELECT) &&  // 0コンのセレクトボタンが押されている状態で
        (TRG(0) & PAD_START))       // 0コンのスタートボタンが押された瞬間
    {
        changeScene(Title::instance());   // タイトルシーンに切り替える
        return;
    }

    // ポーズ処理
    if (TRG(0) & PAD_START)
        isPaused = !isPaused;       // 0コンのスタートボタンが押されたらポーズ状態が反転
    if (isPaused) return;           // この時点でポーズ中ならリターン

    switch (state)
    {
    case 0:
        //////// 初期設定 ////////

        timer = 0;
        GameLib::setBlendMode(Blender::BS_ALPHA);   // 通常のアルファ処理

        // テクスチャの読み込み
        texture::load(loadTexture);

        // プレイヤーマネージャの初期化
        playerManager()->init();

        // プレイヤー（自分で操作）を追加する
        playerManager()->add(&player, VECTOR2(100, 512));

        bgManager()->init(); // BGの初期化


		mapObjManager()->init(bgManager()->getTerrain());

        state++;    // 初期化処理の終了

        /*fallthrough*/     // case 1:の処理も同時に行う必要があるため、わざとbreak;を記述していない

    case 1:


        timer++;

        // プレイヤーの更新
        playerManager()->update();

		wallManager()->update();



		mapObjManager()->update();

		// 各種あたり判定
		judge();

		if (stage == 0) {
			tutorail->update();
		}
        break;
    }
}

//--------------------------------------------------------------
//  描画処理
//--------------------------------------------------------------
void Game::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(0, 0, 0, 1));

	bgManager()->drawBack();     // 背景の描画

	wallManager()->draw();

    
    bgManager()->drawTerrain();  // 地形の描画

    // プレイヤーの描画
    playerManager()->draw();

	

	mapObjManager()->draw();


	if (stage == 0) {
		tutorail->draw();
	}

	/*using namespace input;
	debug::setString("%d", getCursorPosX());
	debug::setString("%d", getCursorPosY());*/
}

//--------------------------------------------------------------
//  終了処理
//--------------------------------------------------------------
void Game::uninit()
{
	state = 0;

    // 各マネージャの解放
    safe_delete(bgManager_);
    safe_delete(playerManager_);
	safe_delete(wallManager_);
	safe_delete(bottanManager_);

	safe_delete(tutorail);
    // テクスチャの解放
    texture::releaseAll();

    // 音楽のクリア
    music::clear();
}

//******************************************************************************
