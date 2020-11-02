#include "all.h"

using namespace GameLib;

//当たり判定
//--------------------------------
//  矩形と矩形のあたり判定
//--------------------------------
bool rectHitCheck(const fRECT& rect1, const fRECT& rect2)
{
	// 条件を満たさなければすぐリターンさせる（早期リターン）
	if (rect1.left > rect2.right)  return false;
	if (rect1.right < rect2.left)   return false;
	if (rect1.top > rect2.bottom) return false;
	if (rect1.bottom < rect2.top)    return false;

	return true;    // あたっている
}

//--------------------------------
//  obj1とobj2が当たっているかどうかのチェック
//--------------------------------
bool judgeCheck(const OBJ2D& obj1, const OBJ2D& obj2, float margin)
{
	if (obj1.judgeFlg == false) return false;
	if (obj2.judgeFlg == false) return false;

	fRECT rect1(
		obj1.position.x - obj1.size.x, obj1.position.y - obj1.size.y,
		obj1.position.x + obj1.size.x, obj1.position.y - margin
	);

	fRECT rect2(
		obj2.position.x - obj2.size.x, obj2.position.y - obj2.size.y,
		obj2.position.x + obj2.size.x, obj2.position.y
	);

	return rectHitCheck(rect1, rect2);
}

//--------------------------------
//  obj1とobj2が当たっているかどうかのチェック
//--------------------------------
bool judgeCheck2(const OBJ2D& obj1, const OBJ2D& obj2)
{
	if (&obj1 == &obj2) return false;           // 同じOBJ2Dならfalseを返す
	return judgeCheck(obj1, obj2);
}

//--------------------------------
//  あたり判定処理
//--------------------------------
void judge()
{
	//==============================================================================
	//  あたり領域の設定
	//==============================================================================

		// プレイヤーのあたり領域の設定
	auto pl = &(*Game::instance()->playerManager()->getList()->begin()); // プレイヤーのアドレスを取得
	pl->hitRect = {
		pl->position.x - pl->size.x,
		pl->position.y - pl->size.y,
		pl->position.x + pl->size.x,
		pl->position.y
	};

	auto pSwitch = Game::instance()->mapObjManager();
	for (auto& swit : *pSwitch->getList())     // 範囲for文で全ての敵を辿る
	{
		VECTOR2 sSize = { swit.scale.x * swit.size.x,swit.scale.y * swit.size.y };
		switch (swit.type) {

		case pSwitch->UP:
			swit.hitRect = {
				swit.position.x - sSize.x,
				swit.position.y - sSize.y,
				swit.position.x + sSize.x,
				swit.position.y
			};
			break;
		case pSwitch->RIGHT:
			swit.hitRect = {
				swit.position.x,
				swit.position.y - sSize.y,
				swit.position.x + sSize.x,
				swit.position.y + sSize.y
			};
			break;
		case pSwitch->DOWN:
			swit.hitRect = {
				swit.position.x - sSize.x,
				swit.position.y,
				swit.position.x + sSize.x,
				swit.position.y + sSize.y
			};
			break;
		case pSwitch->LEFT:
			swit.hitRect = {
				swit.position.x - sSize.x,
				swit.position.y - sSize.y,
				swit.position.x,
				swit.position.y + sSize.y
			};
			break;

			//ゴール
		case pSwitch->GOAL:
			swit.hitRect = {
				swit.position.x - sSize.x,
				swit.position.y - sSize.y,
				swit.position.x + sSize.x,
				swit.position.y + sSize.y
			};
			break;

		}
	}


	for (auto& swit : *pSwitch->getList())     // 範囲for文で全ての敵を辿る
	{
		if (!swit.judgeFlg)continue;
		if (rectHitCheck(pl->hitRect, swit.hitRect))
		{
			// あたっている
			swit.hitFlg = true;

			if (swit.type == pSwitch->GOAL) {
				pl->hitFlg = true;
			}
		}
	}

}
