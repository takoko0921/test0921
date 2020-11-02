//******************************************************************************
//
//
//      �v���C���[�N���X
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//******************************************************************************
//
//      �v���C���[�ړ�����
//
//******************************************************************************


//--------------------------------------------------------------
//  �v���C���[�ʏ펞�̍s��
//--------------------------------------------------------------
void Player::move(OBJ2D* obj)
{
	using namespace input;  // �֐����œ��͏������s���Ƃ��ɋL�q����



	switch (obj->state)
	{
	case 0:
		//////// �����ݒ� ////////
		obj->data = &sprPlayer;

		obj->size = VECTOR2(50 / 2, 34 - 2);

		obj->hitFlg = false;

		obj->state++;

		break;

	case 1:
		//////// �ʏ펞 ////////

		// ���t���[�����̏����ݒ�
		obj->onGround = false;   // �n�ʃt���O�͖��t���[���̍ŏ���false�ɂ��Ă����A�n�ʂɐڂ��Ă�����true��ݒ肷��

		//�d��
		gravity(obj);


		//�ǂɑ΂��Ă̏���
		againstWall(obj);

		//�Q�[���V�[�������}�b�v�`�b�v�̏���������
		if (Game::instance()->getSceneState() == 1) {
			//�}�b�v�`�b�v�ɑ΂��Ă̏���
			againstMapChip(obj);
		}

		//�^�C�g���V�[���ŉ�ʉ������Ƃ���̂ŏ��Ȃǂ̌����������s���ׂɌ��������̑O�ɏ����Ă���
		areaCheck(obj);


		//����
		deceleration(obj);

		if (obj->hitFlg) {
			obj->data = nullptr;
		}

		break;
	}
}

void Player::gravity(OBJ2D* obj) {

	// ���x�ɉ����x��������
	obj->speed.y += KASOKU;

	// �ő呬�x�`�F�b�N
	if (obj->speed.y > SPEED_MAX_Y)
		obj->speed.y = SPEED_MAX_Y;

	obj->position.y += obj->speed.y;
}

void Player::againstWall(OBJ2D* obj) {
	Wall* wallA = nullptr;
	//�V�[���̃X�e�[�g���P�̎��͂��̃V�[���������Ă���B
	//�����̃V�[���Ŏg���̂ł��ꂼ�ꓮ���Ă���V�[���̂������Ă���B
	if (Title::instance()->getSceneState() == 1) {
		wallA = &(*Title::instance()->wallManager()); // �A�h���X���擾
	}
	if (Game::instance()->getSceneState() == 1) {
		wallA = &(*Game::instance()->wallManager()); // �A�h���X���擾
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
	// �}�b�v�`�b�v�����蔻��
	{   // �������`�F�b�N
		if (Game::instance()->bgManager()->isFloor(obj->position.x, obj->position.y, obj->size.x - 5))
		{
			// ���ɂ������Ă�����
			Game::instance()->bgManager()->mapHoseiDown(obj);    //  �������̕␳����
			obj->onGround = true;   // �n�ʃt���O
			{
				if (obj->tHit) {
					Game::instance()->changeScene(Game::instance());   // �^�C�g���V�[���ɐ؂�ւ���
					//Game::instance()->setState(0);
				}
			}
			obj->onGround = true;
		}
		else {
			obj->onGround = false;
		}
	}

	{   // ������`�F�b�N
		if (Game::instance()->bgManager()->isCeiling(
			obj->position.x, obj->position.y - obj->size.y, obj->size.x))
		{
			//�� isCeiling �֐��̖߂�l��true�ł������ꍇ�́A������̕␳�����imapHoseiUp�֐��j���Ă�
			Game::instance()->bgManager()->mapHoseiUp(obj); // ������̕␳����

			if (Game::instance()->bgManager()->isCeiling(
				obj->position.x, obj->position.y - obj->size.y, obj->size.x))
			{
				if (obj->bHit) {
					Game::instance()->changeScene(Game::instance());   // �^�C�g���V�[���ɐ؂�ւ���
					//Game::instance()->setState(0);

				}
			}

		}

	}

	{   // �E�����`�F�b�N
		if (Game::instance()->bgManager()->isWall(obj->position.x + obj->size.x,
			obj->position.y, obj->size.y))
		{
			Game::instance()->bgManager()->mapHoseiRight(obj);     // �E�����̕␳����
			if (obj->lHit) {
				Game::instance()->changeScene(Game::instance());   // �V�[���ɐ؂�ւ���
				//Game::instance()->setState(0);
			}
		}
	}

	{   // �������`�F�b�N
		if (Game::instance()->bgManager()->isWall(obj->position.x - obj->size.x,
			obj->position.y, obj->size.y))
		{
			Game::instance()->bgManager()->mapHoseiLeft(obj);
			if (obj->rHit) {
				Game::instance()->changeScene(Game::instance());   // �^�C�g���V�[���ɐ؂�ւ���
				//Game::instance()->setState(0);
			}
		}
	}


	//�͂�ɓ�����ƍŏ�����
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
		//�n�ʂɂ��Ă��Ȃ����͌����͏��Ȃ�
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
//  ����
//--------------------------------------------------------------
void ErasePlayer::erase(OBJ2D* obj)
{
	obj->mvAlg = nullptr;
}
