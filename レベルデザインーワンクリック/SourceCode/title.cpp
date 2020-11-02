//******************************************************************************
//
//
//      �^�C�g��
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< �ϐ� >----------------------------------------------------------------
Title Title::instance_;

//--------------------------------------------------------------
//  ����������
//--------------------------------------------------------------
void Title::init()
{
	Scene::init();	    // ���N���X��init���Ă�

	playerManager_ = new PlayerManager;
	wallManager_ = new Wall;
	bottonManager_ = new BottonManager;
}
//--------------------------------------------------------------
//  �X�V����
//--------------------------------------------------------------
void Title::update()
{
    using namespace input;

	switch (state)
	{
		{
	case 0:
		//////// �����ݒ� ////////

		timer = 0;                                  // �^�C�}�[��������
		GameLib::setBlendMode(Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

		// �e�N�X�`���̓ǂݍ���
		texture::load(loadTexture);

		// �v���C���[�}�l�[�W���̏�����
		playerManager()->init();

		// �v���C���[�i�����ő���j��ǉ�����
		playerManager()->add(&player, VECTOR2(100, 512));


		auto pBtn = bottonManager();
		bottonManager()->addSpr(pBtn->STAGE0, &sprBotton0, &botton, VECTOR2(720, 170));
		bottonManager()->addSpr(pBtn->STAGE1, &sprBotton0, &botton, VECTOR2(720, 320));
		bottonManager()->addSpr(pBtn->STAGE2, &sprBotton0, &botton, VECTOR2(720, 470));

		state++;                                    // �����������̏I��

		/*fallthrough*/                             // �Ӑ}�I��break;���L�q���Ă��Ȃ�

		}
    case 1:
        //////// �ʏ펞�̏��� ////////

        timer++;                            // �^�C�}�[�𑫂�

		 // �v���C���[�̍X�V
		playerManager()->update();

		wallManager()->update();

		bottonManager()->update();


		//if (TRG(0) & PAD_TRG1) {             // PAD_TRG1�������ꂽ��
		//	changeScene(Game::instance());  // �Q�[���̃X�e�[�W�P�ɐ؂�ւ�
		//	Game::instance()->stage = 1;
		//}
		//if (TRG(0) & PAD_TRG2) {             // PAD_TRG2�������ꂽ��
		//	changeScene(Game::instance());  // �Q�[���̃X�e�[�W�Q�ɐ؂�ւ�
		//	Game::instance()->stage = 2;
		//}

        break;
    }
}

//--------------------------------------------------------------
//  �`�揈��
//--------------------------------------------------------------
void Title::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0.2f, 0.3f, 1.0f, 1));

	using namespace system;
	sprBack.draw(
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2,
		20, 20
	);

	wallManager()->draw();

	// �v���C���[�̕`��
	playerManager()->draw();

	bottonManager()->draw();


    // �^�C�g���\��
    /*font::textOut(4, "ECC COMP", VECTOR2(60, 60), VECTOR2(2.0f, 2.0f), VECTOR4(1, 1, 0, 1));
    font::textOut(4, "Game Programming II", VECTOR2(60, 140), VECTOR2(1.0f, 1.0f), VECTOR4(0, 1, 1, 1));*/
	sprTitle.draw(20, SCREEN_HEIGHT / 2 -100,0.75f, 0.75f);


	font::textOut(4, "CLICK ANY BOTTON!", VECTOR2(550, 70)/*, {0.7f,0.7f }*/);

	font::textOut(4, "TUTORIAL", VECTOR2(600, 160));
	font::textOut(4, "STAGE1", VECTOR2(600, 310));
	font::textOut(4, "STAGE2", VECTOR2(600, 460));


    // "Push Start Button" �_��
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
	// �e�N�X�`���̉��
	texture::releaseAll();

	// ���y�̃N���A
	music::clear();
}
