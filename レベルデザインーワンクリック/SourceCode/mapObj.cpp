//------< インクルード >---------------------------------------------------------
#include "all.h"

using namespace GameLib;


AnimeData animeGoal[] = {
		{ &sprGoal1, 15 },
		{ &sprGoal2, 15 },
		{ &sprGoal3, 15 },
		{ &sprGoal4, 15 },
		{ &sprGoal5, 15 },
		{ &sprGoal6, 0 },
		{ nullptr, -1 },// 終了フラグ
};

AnimeData animeGoal2[] = {
		{ &sprGoal6, 15 },
		{ &sprGoal7, 15 },
		/*{ &sprGoal8, 15 },*/
		{ nullptr, -1 },// 終了フラグ
};



void Switch::move(OBJ2D* obj) {

	switch (obj->state)
	{
		{
	case 0:
		obj->size = { 32 / 2,32 / 2 };
		obj->scale = { 2,2 };


		obj->judgeFlg = true;
		obj->hitFlg = false;

		obj->state++;

		obj->isDrawHitRect = true;
		break;
		}

		{
	case 1:
		auto pSwitch = Game::instance()->mapObjManager();
		if (obj->judgeFlg) {
			if (obj->hitFlg) {
				obj->judgeFlg = false;

				switch (obj->type) {
				case pSwitch->UP:
					obj->position.y += 28;
					break;
				case pSwitch->RIGHT:
					obj->position.x -= 28;
					break;
				case pSwitch->DOWN:
					obj->position.y -= 28;
					break;
				case pSwitch->LEFT:
					obj->position.x += 28;
					break;

				}
			}
		}

		break;

		}
	}
}


void EraseSwitch::erase(OBJ2D* obj)
{

}

void Goal::move(OBJ2D* obj) {
	// 変数
	AnimeData* animeData = nullptr;

	switch (obj->state)
	{
	case 0:
		obj->animeData = animeGoal;

		obj->position.y -= 24;
		obj->size = { 224 / 2,114 / 2 };
		obj->judgeFlg = true;

		obj->state++;
		break;

	case 1:
		//ゴールすると次のステージにしてゲームシーンを初期化する
		if (obj->hitFlg) {
			obj->animeData = animeGoal;


			obj->stayCount++;

			if (obj->stayCount >= 15 * 5) {
				obj->animeData = animeGoal2;
				//obj->data = &sprGoal6;


				if (obj->stayCount >= 20 * 9) {


					Game::instance()->setState(0);
					//Game::instance()->bgManager()->stage++;
					Game::instance()->stage++;
				}
			}
			// アニメーション更新
			obj->animeUpdate();

		}



		break;
	}
}

void EraseGoal::erase(OBJ2D* obj)
{

}


void MapObjManager::init(char terrain[][BG::CHIP_NUM_X])
{
	// 基底クラスのinitを呼ぶ
	OBJ2DManager::init();

	//リストのクリア
	managerList.clear();
	//リストに管理クラスを登録する
	managerList.push_back(Game::instance()->playerManager());
	//managerList.push_back(Game::instance()->wallManager());
	managerList.push_back(Game::instance()->mapObjManager());
	// 生成
	for (int y = 0; y < BG::CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < BG::CHIP_NUM_X; x++)
		{
			VECTOR2 pos = { static_cast<float>(x),static_cast<float>(y) };
			switch (terrain[y][x])
			{
				//RED
			case RED_UP_INDEX: // マップチップの中央下の位置に配置されるBOX
				aAddSpr(UP, &sprSwitch_Red_Up2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Red_Up1, &mapObj, pos);
				terrain[y][x] = -1;     // 用が済んだので地形データを-1（何もなし）にしておく
				break;
			case RED_RIGHT_INDEX: // マップチップの中央下の位置に配置されるBOX
				aAddSpr(RIGHT, &sprSwitch_Red_Right2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Red_Right1, &mapObj, pos);
				terrain[y][x] = -1;     // 用が済んだので地形データを-1（何もなし）にしておく
				break;
			case RED_DOWN_INDEX: // マップチップの中央下の位置に配置されるBOX
				aAddSpr(DOWN, &sprSwitch_Red_Down2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Red_Down1, &mapObj, pos);
				terrain[y][x] = -1;     // 用が済んだので地形データを-1（何もなし）にしておく
				break;
			case RED_LEFT_INDEX: // マップチップの中央下の位置に配置されるBOX
				aAddSpr(LEFT, &sprSwitch_Red_Left2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Red_Left1, &mapObj, pos);
				terrain[y][x] = -1;     // 用が済んだので地形データを-1（何もなし）にしておく
				break;

				//GREEN
			case GREEN_UP_INDEX: // マップチップの中央下の位置に配置されるBOX
				aAddSpr(UP, &sprSwitch_Green_Up2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Green_Up1, &mapObj, pos);
				terrain[y][x] = -1;     // 用が済んだので地形データを-1（何もなし）にしておく
				break;
			case GREEN_RIGHT_INDEX: // マップチップの中央下の位置に配置されるBOX
				aAddSpr(RIGHT, &sprSwitch_Green_Right2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Green_Right1, &mapObj, pos);
				terrain[y][x] = -1;     // 用が済んだので地形データを-1（何もなし）にしておく
				break;
			case GREEN_DOWN_INDEX: // マップチップの中央下の位置に配置されるBOX
				aAddSpr(DOWN, &sprSwitch_Green_Down2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Green_Down1, &mapObj, pos);
				terrain[y][x] = -1;     // 用が済んだので地形データを-1（何もなし）にしておく
				break;
			case GREEN_LEFT_INDEX: // マップチップの中央下の位置に配置されるBOX
				aAddSpr(LEFT, &sprSwitch_Green_Left2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Green_Left1, &mapObj, pos);
				terrain[y][x] = -1;     // 用が済んだので地形データを-1（何もなし）にしておく
				break;

				//BLUE
			case BLUE_UP_INDEX: // マップチップの中央下の位置に配置されるBOX
				aAddSpr(UP, &sprSwitch_Blue_Up2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Blue_Up1, &mapObj, pos);
				terrain[y][x] = -1;     // 用が済んだので地形データを-1（何もなし）にしておく
				break;
			case BLUE_RIGHT_INDEX: // マップチップの中央下の位置に配置されるBOX
				aAddSpr(RIGHT, &sprSwitch_Blue_Right2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Blue_Right1, &mapObj, pos);
				terrain[y][x] = -1;     // 用が済んだので地形データを-1（何もなし）にしておく
				break;
			case BLUE_DOWN_INDEX: // マップチップの中央下の位置に配置されるBOX
				aAddSpr(DOWN, &sprSwitch_Blue_Down2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Blue_Down1, &mapObj, pos);
				terrain[y][x] = -1;     // 用が済んだので地形データを-1（何もなし）にしておく
				break;
			case BLUE_LEFT_INDEX: // マップチップの中央下の位置に配置されるBOX
				aAddSpr(LEFT, &sprSwitch_Blue_Left2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Blue_Left1, &mapObj, pos);
				terrain[y][x] = -1;     // 用が済んだので地形データを-1（何もなし）にしておく
				break;

			case GOAL_INDEX:
				aAddSpr(GOAL, &sprGoal1, &goal, pos);
				terrain[y][x] = -1;     // 用が済んだので地形データを-1（何もなし）にしておく
				break;

			}
		}
	}
}

