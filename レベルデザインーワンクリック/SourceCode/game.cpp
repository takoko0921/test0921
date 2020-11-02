//******************************************************************************
//
//
//      �Q�[��
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< �ϐ� >----------------------------------------------------------------
Game Game::instance_;

//--------------------------------------------------------------
//  ����������
//--------------------------------------------------------------
void Game::init()
{
    Scene::init();	    // ���N���X��init���Ă�

    playerManager_      = new PlayerManager;
    bgManager_          = new BG;
	wallManager_		= new Wall;
	bottanManager_		= new MapObjManager;

	tutorail = new Tutorial;
		

    isPaused = false;   // �|�[�Y�t���O�̏�����
}

//--------------------------------------------------------------
//  �X�V����
//--------------------------------------------------------------
void Game::update()
{
    using namespace input;

    // �\�t�g���Z�b�g
    if ((STATE(0) & PAD_SELECT) &&  // 0�R���̃Z���N�g�{�^����������Ă����Ԃ�
        (TRG(0) & PAD_START))       // 0�R���̃X�^�[�g�{�^���������ꂽ�u��
    {
        changeScene(Title::instance());   // �^�C�g���V�[���ɐ؂�ւ���
        return;
    }

    // �|�[�Y����
    if (TRG(0) & PAD_START)
        isPaused = !isPaused;       // 0�R���̃X�^�[�g�{�^���������ꂽ��|�[�Y��Ԃ����]
    if (isPaused) return;           // ���̎��_�Ń|�[�Y���Ȃ烊�^�[��

    switch (state)
    {
    case 0:
        //////// �����ݒ� ////////

        timer = 0;
        GameLib::setBlendMode(Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        // �e�N�X�`���̓ǂݍ���
        texture::load(loadTexture);

        // �v���C���[�}�l�[�W���̏�����
        playerManager()->init();

        // �v���C���[�i�����ő���j��ǉ�����
        playerManager()->add(&player, VECTOR2(100, 512));

        bgManager()->init(); // BG�̏�����


		mapObjManager()->init(bgManager()->getTerrain());

        state++;    // �����������̏I��

        /*fallthrough*/     // case 1:�̏����������ɍs���K�v�����邽�߁A�킴��break;���L�q���Ă��Ȃ�

    case 1:


        timer++;

        // �v���C���[�̍X�V
        playerManager()->update();

		wallManager()->update();



		mapObjManager()->update();

		// �e�킠���蔻��
		judge();

		if (stage == 0) {
			tutorail->update();
		}
        break;
    }
}

//--------------------------------------------------------------
//  �`�揈��
//--------------------------------------------------------------
void Game::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0, 0, 0, 1));

	bgManager()->drawBack();     // �w�i�̕`��

	wallManager()->draw();

    
    bgManager()->drawTerrain();  // �n�`�̕`��

    // �v���C���[�̕`��
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
//  �I������
//--------------------------------------------------------------
void Game::uninit()
{
	state = 0;

    // �e�}�l�[�W���̉��
    safe_delete(bgManager_);
    safe_delete(playerManager_);
	safe_delete(wallManager_);
	safe_delete(bottanManager_);

	safe_delete(tutorail);
    // �e�N�X�`���̉��
    texture::releaseAll();

    // ���y�̃N���A
    music::clear();
}

//******************************************************************************
