//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

using namespace GameLib;


AnimeData animeGoal[] = {
		{ &sprGoal1, 15 },
		{ &sprGoal2, 15 },
		{ &sprGoal3, 15 },
		{ &sprGoal4, 15 },
		{ &sprGoal5, 15 },
		{ &sprGoal6, 0 },
		{ nullptr, -1 },// �I���t���O
};

AnimeData animeGoal2[] = {
		{ &sprGoal6, 15 },
		{ &sprGoal7, 15 },
		/*{ &sprGoal8, 15 },*/
		{ nullptr, -1 },// �I���t���O
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
	// �ϐ�
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
		//�S�[������Ǝ��̃X�e�[�W�ɂ��ăQ�[���V�[��������������
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
			// �A�j���[�V�����X�V
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
	// ���N���X��init���Ă�
	OBJ2DManager::init();

	//���X�g�̃N���A
	managerList.clear();
	//���X�g�ɊǗ��N���X��o�^����
	managerList.push_back(Game::instance()->playerManager());
	//managerList.push_back(Game::instance()->wallManager());
	managerList.push_back(Game::instance()->mapObjManager());
	// ����
	for (int y = 0; y < BG::CHIP_NUM_Y; y++)
	{
		for (int x = 0; x < BG::CHIP_NUM_X; x++)
		{
			VECTOR2 pos = { static_cast<float>(x),static_cast<float>(y) };
			switch (terrain[y][x])
			{
				//RED
			case RED_UP_INDEX: // �}�b�v�`�b�v�̒������̈ʒu�ɔz�u�����BOX
				aAddSpr(UP, &sprSwitch_Red_Up2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Red_Up1, &mapObj, pos);
				terrain[y][x] = -1;     // �p���ς񂾂̂Œn�`�f�[�^��-1�i�����Ȃ��j�ɂ��Ă���
				break;
			case RED_RIGHT_INDEX: // �}�b�v�`�b�v�̒������̈ʒu�ɔz�u�����BOX
				aAddSpr(RIGHT, &sprSwitch_Red_Right2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Red_Right1, &mapObj, pos);
				terrain[y][x] = -1;     // �p���ς񂾂̂Œn�`�f�[�^��-1�i�����Ȃ��j�ɂ��Ă���
				break;
			case RED_DOWN_INDEX: // �}�b�v�`�b�v�̒������̈ʒu�ɔz�u�����BOX
				aAddSpr(DOWN, &sprSwitch_Red_Down2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Red_Down1, &mapObj, pos);
				terrain[y][x] = -1;     // �p���ς񂾂̂Œn�`�f�[�^��-1�i�����Ȃ��j�ɂ��Ă���
				break;
			case RED_LEFT_INDEX: // �}�b�v�`�b�v�̒������̈ʒu�ɔz�u�����BOX
				aAddSpr(LEFT, &sprSwitch_Red_Left2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Red_Left1, &mapObj, pos);
				terrain[y][x] = -1;     // �p���ς񂾂̂Œn�`�f�[�^��-1�i�����Ȃ��j�ɂ��Ă���
				break;

				//GREEN
			case GREEN_UP_INDEX: // �}�b�v�`�b�v�̒������̈ʒu�ɔz�u�����BOX
				aAddSpr(UP, &sprSwitch_Green_Up2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Green_Up1, &mapObj, pos);
				terrain[y][x] = -1;     // �p���ς񂾂̂Œn�`�f�[�^��-1�i�����Ȃ��j�ɂ��Ă���
				break;
			case GREEN_RIGHT_INDEX: // �}�b�v�`�b�v�̒������̈ʒu�ɔz�u�����BOX
				aAddSpr(RIGHT, &sprSwitch_Green_Right2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Green_Right1, &mapObj, pos);
				terrain[y][x] = -1;     // �p���ς񂾂̂Œn�`�f�[�^��-1�i�����Ȃ��j�ɂ��Ă���
				break;
			case GREEN_DOWN_INDEX: // �}�b�v�`�b�v�̒������̈ʒu�ɔz�u�����BOX
				aAddSpr(DOWN, &sprSwitch_Green_Down2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Green_Down1, &mapObj, pos);
				terrain[y][x] = -1;     // �p���ς񂾂̂Œn�`�f�[�^��-1�i�����Ȃ��j�ɂ��Ă���
				break;
			case GREEN_LEFT_INDEX: // �}�b�v�`�b�v�̒������̈ʒu�ɔz�u�����BOX
				aAddSpr(LEFT, &sprSwitch_Green_Left2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Green_Left1, &mapObj, pos);
				terrain[y][x] = -1;     // �p���ς񂾂̂Œn�`�f�[�^��-1�i�����Ȃ��j�ɂ��Ă���
				break;

				//BLUE
			case BLUE_UP_INDEX: // �}�b�v�`�b�v�̒������̈ʒu�ɔz�u�����BOX
				aAddSpr(UP, &sprSwitch_Blue_Up2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Blue_Up1, &mapObj, pos);
				terrain[y][x] = -1;     // �p���ς񂾂̂Œn�`�f�[�^��-1�i�����Ȃ��j�ɂ��Ă���
				break;
			case BLUE_RIGHT_INDEX: // �}�b�v�`�b�v�̒������̈ʒu�ɔz�u�����BOX
				aAddSpr(RIGHT, &sprSwitch_Blue_Right2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Blue_Right1, &mapObj, pos);
				terrain[y][x] = -1;     // �p���ς񂾂̂Œn�`�f�[�^��-1�i�����Ȃ��j�ɂ��Ă���
				break;
			case BLUE_DOWN_INDEX: // �}�b�v�`�b�v�̒������̈ʒu�ɔz�u�����BOX
				aAddSpr(DOWN, &sprSwitch_Blue_Down2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Blue_Down1, &mapObj, pos);
				terrain[y][x] = -1;     // �p���ς񂾂̂Œn�`�f�[�^��-1�i�����Ȃ��j�ɂ��Ă���
				break;
			case BLUE_LEFT_INDEX: // �}�b�v�`�b�v�̒������̈ʒu�ɔz�u�����BOX
				aAddSpr(LEFT, &sprSwitch_Blue_Left2, &mapObj, pos);
				aAddSpr(STAND, &sprSwitch_Blue_Left1, &mapObj, pos);
				terrain[y][x] = -1;     // �p���ς񂾂̂Œn�`�f�[�^��-1�i�����Ȃ��j�ɂ��Ă���
				break;

			case GOAL_INDEX:
				aAddSpr(GOAL, &sprGoal1, &goal, pos);
				terrain[y][x] = -1;     // �p���ς񂾂̂Œn�`�f�[�^��-1�i�����Ȃ��j�ɂ��Ă���
				break;

			}
		}
	}
}

