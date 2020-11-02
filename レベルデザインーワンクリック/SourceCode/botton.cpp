#include "all.h"
using namespace GameLib;


void Botton::move(OBJ2D* obj) {
	using namespace input;

	switch (obj->state)
	{
	case 0:

		obj->size = VECTOR2(288 / 2, 48 / 2);
		//obj->scale = { 1.5f,1.5f };
		obj->judgeFlg = true;

		obj->state++;

		break;

		{
	case 1:
		for (auto& btn : *Title::instance()->bottonManager()->getList()) {
			if (btn.hitFlg) {
				obj->judgeFlg = false;
			}
		}

		if (obj->judgeFlg) {
			if (TRG(0) & PAD_TRG4) {//ƒ}ƒEƒX¶
				VECTOR2 curPos = VECTOR2(getCursorPosX(), getCursorPosY());

				if (obj->position.x - obj->size.x < curPos.x && obj->position.x + obj->size.x > curPos.x&&
					obj->position.y - obj->size.y < curPos.y && obj->position.y + obj->size.y > curPos.y)
				{
					auto pBtn = Title::instance()->bottonManager();
					switch (obj->type) {
					case pBtn->STAGE0:
						Game::instance()->stage = 0;
						break;
					case pBtn->STAGE1:
						Game::instance()->stage = 1;
						break;
					case pBtn->STAGE2:
						Game::instance()->stage = 2;
						break;

					}
					obj->hitFlg = true;
					obj->data = &sprBotton1;
				}
			}
		}
		break;
		}
	}
}

void EraseBotton::erase(OBJ2D* obj)
{
	obj->mvAlg = nullptr;
}