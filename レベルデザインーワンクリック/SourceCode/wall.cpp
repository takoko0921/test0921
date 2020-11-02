////------< インクルード >----------------------------------------------------------
#include "all.h"
//
////------< using >---------------------------------------------------------------
using namespace GameLib;

void Wall::update() {
	using namespace input;

	OBJ2D* pl = nullptr;

	//シーンのステートが１の時はそのシーンが動いている。
	//複数のシーンで使うのでそれぞれ動いているシーンのを持ってくる。
	if (Title::instance()->getSceneState() == 1) {
		pl = &(*Title::instance()->playerManager()->getList()->begin()); // アドレスを取得
	}

	if (Game::instance()->getSceneState() == 1) {
		pl = &(*Game::instance()->playerManager()->getList()->begin()); // アドレスを取得
	}

	//ゲーム画面
	if (Game::instance()->getSceneState() == 1) 
	{

		//移動している時は入力を受け付けない
		if (moveFlg == false) {

			//四角が外側に元に戻るようにする
			if (vec2LengthSq(VECTOR2(0, 0) - mLeftTop) > 1
				|| vec2LengthSq(VECTOR2(system::SCREEN_WIDTH, system::SCREEN_HEIGHT) - mRightBottom) > 1) {

				stayCount++;
				//20フレーム待つ
				if (stayCount > 20) {

					mLeftTop += anyFlameArrive(30, speedLT,  started, mLeftTop, { 0,0 });
					mRightBottom += anyFlameArrive(30, speedRB,started, mRightBottom, { system::SCREEN_WIDTH,system::SCREEN_HEIGHT });
					//始点と終点から四角を作る
					mRightTop = { mRightBottom.x,mLeftTop.y };
					mLeftBottom = { mLeftTop.x,mRightBottom.y };



					started = true;

				}

			}


			//左クリックで始点を決める
			if (TRG(0) & PAD_TRG4) {//マウス左
				//左クリックした点を始点
				leftTop = VECTOR2(getCursorPosX(), getCursorPosY());
				//左クリックが押された
				clicked = true;
			}

			//TRGが押された時だけ四角を作り始める
			//移動している時からのクリックし続ているのを受け付けない
			if (clicked == true) {
				if (STATE(0) & PAD_TRG4) {//マウス左
					//今左クリックしている点を終点
					rightBottom = VECTOR2(getCursorPosX(), getCursorPosY());
					//始点と終点から四角を作る							
					rightTop = { rightBottom.x,leftTop.y };
					leftBottom = { leftTop.x,rightBottom.y };

					//目標となる四角の頂点を選ぶ（四角が交差しないようにする）
					//左上が始点、右下が終点
					if (leftTop.x < rightBottom.x
						&& leftTop.y < rightBottom.y) {
						LT = leftTop;
						RB = rightBottom;
					}
					//右上が始点、左下が終点
					if (leftTop.x > rightBottom.x
						&& leftTop.y < rightBottom.y) {
						LT = rightTop;
						RB = leftBottom;
					}
					//左下が始点、右上が終点
					if (leftTop.x < rightBottom.x
						&& leftTop.y > rightBottom.y) {
						LT = leftBottom;
						RB = rightTop;
					}
					//右下が始点、左上が終点
					if (leftTop.x > rightBottom.x
						&& leftTop.y > rightBottom.y) {
						LT = rightBottom;
						RB = leftTop;
					}

				}
				if (TRG_RELEASE(0) & PAD_TRG4) {//マウス左
					//始点と終点からできる四角がある程度の大きさ
					if (RB.x - LT.x > 70
						&& RB.y - LT.y > 70) {
						moveFlg = true;
						started = false;
					}
					else {
						moveFlg = false;


					}
					clicked = false;
				}

			}
		}


		//クリック離すまで始めない
		if (moveFlg == true) {
			if (vec2LengthSq(LT - mLeftTop) > 1
				|| vec2LengthSq(RB - mRightBottom) > 1) {
				//指定した四角に向かう
				mLeftTop += anyFlameArrive(40, speedLT, started, mLeftTop, LT);
				mRightBottom += anyFlameArrive(40, speedRB, started, mRightBottom, RB);
				//始点と終点から四角を作る
				mRightTop = { mRightBottom.x,mLeftTop.y };
				mLeftBottom = { mLeftTop.x,mRightBottom.y };


				//初めの距離が欲しいのでここをループする一回目が終わった後にフラグを立てる
				started = true;
			}
			else {

				moveFlg = false;

				LT = {};
				RB = {};

				started = false;
				stayCount = 0;

				//慣性をつける
				if (pl->lHit)pl->speed.x = speedLT.x * 0.5;
				if (pl->rHit)pl->speed.x = speedRB.x * 0.5;
				if (pl->tHit)pl->speed.y = speedLT.y * 0.5;
				if (pl->bHit)pl->speed.y = speedRB.y * 0.5;


			}
		}
	}

	//タイトル画面
	if (Title::instance()->getSceneState() == 1) {

		if (!moveFlg) {
			for (auto& btn : *Title::instance()->bottonManager()->getList()) {
				if (btn.hitFlg) {
					LT = { btn.position.x - btn.size.x,btn.position.y - btn.size.y };
					RB = { btn.position.x + btn.size.x,btn.position.y + btn.size.y };

					toBtnFlg = true;
					moveFlg = true;
				}
			}

			stayCount++;

			if (stayCount == 30) {
				LT = { 555,220 };
				RB = { 805,410 };

				moveFlg = true;
			}
			if (stayCount == 50) {
				LT = { 0,0 };
				RB = { system::SCREEN_WIDTH,system::SCREEN_HEIGHT };

				moveFlg = true;
			}
			if (stayCount == 80) {
				LT = { 155,220 };
				RB = { 405,410 };

				moveFlg = true;
			}
			if (stayCount == 100) {
				LT = { 0,0 };
				RB = { system::SCREEN_WIDTH,system::SCREEN_HEIGHT };

				moveFlg = true;

				stayCount = 0;
			}

		}

		if (moveFlg) {
			if (vec2LengthSq(LT - mLeftTop) > 1
				|| vec2LengthSq(RB - mRightBottom) > 1) {
				//指定した四角に向かう
				mLeftTop += anyFlameArrive(40, speedLT, started, mLeftTop, LT);
				mRightBottom += anyFlameArrive(40, speedRB, started, mRightBottom, RB);
				//始点と終点から四角を作る
				mRightTop = { mRightBottom.x,mLeftTop.y };
				mLeftBottom = { mLeftTop.x,mRightBottom.y };


				//初めの距離が欲しいのでここをループする一回目が終わった後にフラグを立てる
				started = true;
			}
			else {
				moveFlg = false;
				started = false;


				LT = {};
				RB = {};

				//慣性をつける
				if (pl->lHit)pl->speed.x = speedLT.x * 0.5;
				if (pl->rHit)pl->speed.x = speedRB.x * 0.5;
				if (pl->tHit)pl->speed.y = speedLT.y * 0.5;
				if (pl->bHit)pl->speed.y = speedRB.y * 0.5;

				if (toBtnFlg) {
					Title::instance()->changeScene(Game::instance());  // ゲームのステージに切り替え
				}
			}
		}
	}
}

void Wall::draw() {

	if (Game::instance()->getSceneState() == 1) {
		if (clicked || moveFlg) {
			VECTOR4 col = { 1,1,1,0.3 };

			if (RB.x - LT.x > 70
				&& RB.y - LT.y > 70) {
				col = { 1,1,1,1 };
			}

			primitive::circle(leftTop, 10,col);
			primitive::circle(rightTop, 10, col);
			primitive::circle(leftBottom, 10, col);
			primitive::circle(rightBottom, 10, col);

			primitive::line(leftTop, rightTop, col);
			primitive::line(leftBottom, rightBottom, col);
			primitive::line(leftTop, leftBottom, col);
			primitive::line(rightTop, rightBottom, col);

			

		}
	}

	using namespace system;

	//上
	data->draw(
		SCREEN_WIDTH / 2,
		mLeftTop.y,
		scale.x, scale.y,
		ToRadian(180)
	);
	//下
	data->draw(
		SCREEN_WIDTH / 2,
		mRightBottom.y,
		scale.x, scale.y,
		ToRadian(0)
	);
	//左
	data->draw(
		mLeftTop.x,
		SCREEN_HEIGHT / 2,
		scale.x, scale.y,
		ToRadian(90)
	);
	//右
	data->draw(
		mRightBottom.x,
		SCREEN_HEIGHT / 2,
		scale.x, scale.y,
		ToRadian(270)
	);
}

//VECTOR2 Wall::arrive(VECTOR2& speed, VECTOR2 chacer, VECTOR2 target) {
//	VECTOR2 acc = vec2Normalize(target - chacer) * wallSpeed;
//	//求めたベクトル分加速
//	speed += acc;
//	float dist = vec2Length(target - chacer);
//	if (dist > arriveDist) {
//		//制御
//		if (vec2LengthSq(speed) > maxSpeed* maxSpeed) {
//			speed = vec2Normalize(speed) * maxSpeed;
//		}
//	}
//	else {
//		//近くまでくると減速
//		speed = vec2Normalize(speed) * maxSpeed * dist / arriveDist;
//	}
//	return speed;
//}


VECTOR2 Wall::anyFlameArrive(int moveFlame, VECTOR2& speed, bool started, VECTOR2 chacer, VECTOR2 target) {
	//moveFlameで指定されたフレーム分でtargetの場所までchacerが到着するように動かせる関数
	if (!started) {
		VECTOR2 toTarget = target - chacer;
		speed = toTarget / moveFlame;
	}
	if (vec2LengthSq(target - chacer) > 1) {
		return speed;
	}
	else {
		return {};
	}
}




