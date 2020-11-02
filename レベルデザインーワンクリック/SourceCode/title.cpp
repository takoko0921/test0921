//******************************************************************************
//
//
//      タイトル
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< 変数 >----------------------------------------------------------------
Title Title::instance_;

//--------------------------------------------------------------
//  初期化処理
//--------------------------------------------------------------
void Title::init()
{
	Scene::init();	    // 基底クラスのinitを呼ぶ

	playerManager_ = new PlayerManager;
	wallManager_ = new Wall;
	bottonManager_ = new BottonManager;
}
//--------------------------------------------------------------
//  更新処理
//--------------------------------------------------------------
void Title::update()
{
    using namespace input;

	switch (state)
	{
		{
	case 0:
		//////// 初期設定 ////////

		timer = 0;                                  // タイマーを初期化
		GameLib::setBlendMode(Blender::BS_ALPHA);   // 通常のアルファ処理

		// テクスチャの読み込み
		texture::load(loadTexture);

		// プレイヤーマネージャの初期化
		playerManager()->init();

		// プレイヤー（自分で操作）を追加する
		playerManager()->add(&player, VECTOR2(100, 512));


		auto pBtn = bottonManager();
		bottonManager()->addSpr(pBtn->STAGE0, &sprBotton0, &botton, VECTOR2(720, 170));
		bottonManager()->addSpr(pBtn->STAGE1, &sprBotton0, &botton, VECTOR2(720, 320));
		bottonManager()->addSpr(pBtn->STAGE2, &sprBotton0, &botton, VECTOR2(720, 470));

		state++;                                    // 初期化処理の終了

		/*fallthrough*/                             // 意図的にbreak;を記述していない

		}
    case 1:
        //////// 通常時の処理 ////////

        timer++;                            // タイマーを足す

		 // プレイヤーの更新
		playerManager()->update();

		wallManager()->update();

		bottonManager()->update();


		//if (TRG(0) & PAD_TRG1) {             // PAD_TRG1が押されたら
		//	changeScene(Game::instance());  // ゲームのステージ１に切り替え
		//	Game::instance()->stage = 1;
		//}
		//if (TRG(0) & PAD_TRG2) {             // PAD_TRG2が押されたら
		//	changeScene(Game::instance());  // ゲームのステージ２に切り替え
		//	Game::instance()->stage = 2;
		//}

        break;
    }
}

//--------------------------------------------------------------
//  描画処理
//--------------------------------------------------------------
void Title::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(0.2f, 0.3f, 1.0f, 1));

	using namespace system;
	sprBack.draw(
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2,
		20, 20
	);

	wallManager()->draw();

	// プレイヤーの描画
	playerManager()->draw();

	bottonManager()->draw();


    // タイトル表示
    /*font::textOut(4, "ECC COMP", VECTOR2(60, 60), VECTOR2(2.0f, 2.0f), VECTOR4(1, 1, 0, 1));
    font::textOut(4, "Game Programming II", VECTOR2(60, 140), VECTOR2(1.0f, 1.0f), VECTOR4(0, 1, 1, 1));*/
	sprTitle.draw(20, SCREEN_HEIGHT / 2 -100,0.75f, 0.75f);


	font::textOut(4, "CLICK ANY BOTTON!", VECTOR2(550, 70)/*, {0.7f,0.7f }*/);

	font::textOut(4, "TUTORIAL", VECTOR2(600, 160));
	font::textOut(4, "STAGE1", VECTOR2(600, 310));
	font::textOut(4, "STAGE2", VECTOR2(600, 460));


    // "Push Start Button" 点滅
    /*if ((timer / 40) % 2)
    {
        font::textOut(4, "Push Start Button ", VECTOR2(220, 360));
    }*/
	/*using namespace input;
	debug::setString("%d", getCursorPosX());
	debug::setString("%d", getCursorPosY());*/
}

//******************************************************************************

void Title::uninit() {
	state = 0;

	safe_delete(playerManager_);
	safe_delete(wallManager_);
	safe_delete(bottonManager_);
	// テクスチャの解放
	texture::releaseAll();

	// 音楽のクリア
	music::clear();
}
