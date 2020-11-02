//******************************************************************************
//
//
//      プレイヤークラス
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//******************************************************************************
//
//      プレイヤー移動処理
//
//******************************************************************************


//--------------------------------------------------------------
//  プレイヤー通常時の行動
//--------------------------------------------------------------
void Player::move(OBJ2D* obj)
{
	using namespace input;  // 関数内で入力処理を行うときに記述する



	switch (obj->state)
	{
	case 0:
		//////// 初期設定 ////////
		obj->data = &sprPlayer;

		obj->size = VECTOR2(50 / 2, 34 - 2);

		obj->hitFlg = false;

		obj->state++;

		break;

	case 1:
		//////// 通常時 ////////

		// 毎フレーム毎の初期設定
		obj->onGround = false;   // 地面フラグは毎フレームの最初にfalseにしておき、地面に接していたらtrueを設定する

		//重力
		gravity(obj);


		//壁に対しての処理
		againstWall(obj);

		//ゲームシーンだけマップチップの処理をする
		if (Game::instance()->getSceneState() == 1) {
			//マップチップに対しての処理
			againstMapChip(obj);
		}

		//タイトルシーンで画面下を床とするので床などの減速処理を行う為に減速処理の前に書いている
		areaCheck(obj);


		//減速
		deceleration(obj);

		if (obj->hitFlg) {
			obj->data = nullptr;
		}

		break;
	}
}

void Player::gravity(OBJ2D* obj) {

	// 速度に加速度を加える
	obj->speed.y += KASOKU;

	// 最大速度チェック
	if (obj->speed.y > SPEED_MAX_Y)
		obj->speed.y = SPEED_MAX_Y;

	obj->position.y += obj->speed.y;
}

void Player::againstWall(OBJ2D* obj) {
	Wall* wallA = nullptr;
	//シーンのステートが１の時はそのシーンが動いている。
	//複数のシーンで使うのでそれぞれ動いているシーンのを持ってくる。
	if (Title::instance()->getSceneState() == 1) {
		wallA = &(*Title::instance()->wallManager()); // アドレスを取得
	}
	if (Game::instance()->getSceneState() == 1) {
		wallA = &(*Game::instance()->wallManager()); // アドレスを取得
	}


	if (wallA->moveFlg) {
		if (obj->position.x < wallA->mLeftTop.x + obj->size.x)
		{
			obj->position.x = wallA->mLeftTop.x + obj->size.x;

			obj->lHit = true;
		}
		else {
			obj->lHit = false;
		}

		if (obj->position.x > wallA->mRightBottom.x - obj->size.x)
		{
			obj->position.x = wallA->mRightBottom.x - obj->size.x;

			obj->rHit = true;
		}
		else {
			obj->rHit = false;
		}

		if (obj->position.y < wallA->mLeftTop.y + obj->size.y)
		{
			obj->position.y = wallA->mLeftTop.y + obj->size.y;

			obj->tHit = true;
		}
		else {
			obj->tHit = false;
		}


		if (obj->position.y > wallA->mRightBottom.y)
		{
			obj->position.y = wallA->mRightBottom.y;

			obj->bHit = true;
			obj->onGround = true;
		}
		else {
			obj->bHit = false;
		}

	}
	else {
		obj->lHit = false;
		obj->rHit = false;
		obj->tHit = false;
		obj->bHit = false;

		if (obj->position.x < wallA->mLeftTop.x + obj->size.x)
		{
			obj->speed.x = 0;
		}
		if (obj->position.x > wallA->mRightBottom.x - obj->size.x)
		{
			obj->speed.x = 0;
		}
		if (obj->position.y < wallA->mLeftTop.y + obj->size.y)
		{
			obj->speed.y = 0;
		}
		if (obj->position.y > wallA->mRightBottom.y)
		{
			obj->speed.y = 0;
		}

	}
}

void Player::againstMapChip(OBJ2D* obj) {
	// マップチップ当たり判定
	{   // 下方向チェック
		if (Game::instance()->bgManager()->isFloor(obj->position.x, obj->position.y, obj->size.x - 5))
		{
			// 床にあたっていたら
			Game::instance()->bgManager()->mapHoseiDown(obj);    //  下方向の補正処理
			obj->onGround = true;   // 地面フラグ
			{
				if (obj->tHit) {
					Game::instance()->changeScene(Game::instance());   // タイトルシーンに切り替える
					//Game::instance()->setState(0);
				}
			}
			obj->onGround = true;
		}
		else {
			obj->onGround = false;
		}
	}

	{   // 上方向チェック
		if (Game::instance()->bgManager()->isCeiling(
			obj->position.x, obj->position.y - obj->size.y, obj->size.x))
		{
			//□ isCeiling 関数の戻り値がtrueであった場合は、上方向の補正処理（mapHoseiUp関数）を呼ぶ
			Game::instance()->bgManager()->mapHoseiUp(obj); // 上方向の補正処理

			if (Game::instance()->bgManager()->isCeiling(
				obj->position.x, obj->position.y - obj->size.y, obj->size.x))
			{
				if (obj->bHit) {
					Game::instance()->changeScene(Game::instance());   // タイトルシーンに切り替える
					//Game::instance()->setState(0);

				}
			}

		}

	}

	{   // 右方向チェック
		if (Game::instance()->bgManager()->isWall(obj->position.x + obj->size.x,
			obj->position.y, obj->size.y))
		{
			Game::instance()->bgManager()->mapHoseiRight(obj);     // 右方向の補正処理
			if (obj->lHit) {
				Game::instance()->changeScene(Game::instance());   // シーンに切り替える
				//Game::instance()->setState(0);
			}
		}
	}

	{   // 左方向チェック
		if (Game::instance()->bgManager()->isWall(obj->position.x - obj->size.x,
			obj->position.y, obj->size.y))
		{
			Game::instance()->bgManager()->mapHoseiLeft(obj);
			if (obj->rHit) {
				Game::instance()->changeScene(Game::instance());   // タイトルシーンに切り替える
				//Game::instance()->setState(0);
			}
		}
	}


	//はりに当たると最初から
	{
		if (Game::instance()->bgManager()->isNeedle(obj->position.x,
			obj->position.y, obj->size.x - 7, obj->size.y))
		{
			Game::instance()->changeScene(Game::instance());
			//Game::instance()->setState(0);
		}
	}
}

void Player::areaCheck(OBJ2D* obj) {

	if (obj->position.x < 0 + obj->size.x)
	{
		obj->position.x = obj->size.x;
		obj->speed.x = 0;
	}
	if (obj->position.x > BG::WIDTH - obj->size.x)
	{
		obj->position.x -= BG::WIDTH - obj->size.x;
		obj->speed.x = 0;
	}
	if (obj->position.y < obj->size.y)
	{
		obj->position.y = obj->size.y;
		obj->speed.y = 0;
	}
	if (obj->position.y > BG::HEIGHT)
	{
		obj->position.y = BG::HEIGHT;
		obj->speed.y = 0;

		obj->onGround = true;
	}
}

void Player::deceleration(OBJ2D* obj) {
	if (obj->onGround) {
		if (obj->speed.x > 0) {
			obj->position.x += obj->speed.x;
			obj->speed.x *= 0.8f;
			if (obj->speed.x < 0.1)obj->speed.x = 0;
		}
		if (obj->speed.x < 0) {
			obj->position.x += obj->speed.x;
			obj->speed.x *= 0.8f;
			if (obj->speed.x > 0.1)obj->speed.x = 0;
		}
	}
	else {
		//地面についていない時は減速は少ない
		if (obj->speed.x > 0) {
			obj->position.x += obj->speed.x;
			obj->speed.x *= 0.98f;
			if (obj->speed.x < 0.1)obj->speed.x = 0;
		}
		if (obj->speed.x < 0) {
			obj->position.x += obj->speed.x;
			obj->speed.x *= 0.98f;
			if (obj->speed.x > 0.1)obj->speed.x = 0;
		}
	}
}


//--------------------------------------------------------------
//  消去
//--------------------------------------------------------------
void ErasePlayer::erase(OBJ2D* obj)
{
	obj->mvAlg = nullptr;
}
