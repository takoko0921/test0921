////------< �C���N���[�h >----------------------------------------------------------
#include "all.h"
//
////------< using >---------------------------------------------------------------
using namespace GameLib;

void Wall::update() {
	using namespace input;

	OBJ2D* pl = nullptr;

	//�V�[���̃X�e�[�g���P�̎��͂��̃V�[���������Ă���B
	//�����̃V�[���Ŏg���̂ł��ꂼ�ꓮ���Ă���V�[���̂������Ă���B
	if (Title::instance()->getSceneState() == 1) {
		pl = &(*Title::instance()->playerManager()->getList()->begin()); // �A�h���X���擾
	}

	if (Game::instance()->getSceneState() == 1) {
		pl = &(*Game::instance()->playerManager()->getList()->begin()); // �A�h���X���擾
	}

	//�Q�[�����
	if (Game::instance()->getSceneState() == 1) 
	{

		//�ړ����Ă��鎞�͓��͂��󂯕t���Ȃ�
		if (moveFlg == false) {

			//�l�p���O���Ɍ��ɖ߂�悤�ɂ���
			if (vec2LengthSq(VECTOR2(0, 0) - mLeftTop) > 1
				|| vec2LengthSq(VECTOR2(system::SCREEN_WIDTH, system::SCREEN_HEIGHT) - mRightBottom) > 1) {

				stayCount++;
				//20�t���[���҂�
				if (stayCount > 20) {

					mLeftTop += anyFlameArrive(30, speedLT,  started, mLeftTop, { 0,0 });
					mRightBottom += anyFlameArrive(30, speedRB,started, mRightBottom, { system::SCREEN_WIDTH,system::SCREEN_HEIGHT });
					//�n�_�ƏI�_����l�p�����
					mRightTop = { mRightBottom.x,mLeftTop.y };
					mLeftBottom = { mLeftTop.x,mRightBottom.y };



					started = true;

				}

			}


			//���N���b�N�Ŏn�_�����߂�
			if (TRG(0) & PAD_TRG4) {//�}�E�X��
				//���N���b�N�����_���n�_
				leftTop = VECTOR2(getCursorPosX(), getCursorPosY());
				//���N���b�N�������ꂽ
				clicked = true;
			}

			//TRG�������ꂽ�������l�p�����n�߂�
			//�ړ����Ă��鎞����̃N���b�N�����Ă���̂��󂯕t���Ȃ�
			if (clicked == true) {
				if (STATE(0) & PAD_TRG4) {//�}�E�X��
					//�����N���b�N���Ă���_���I�_
					rightBottom = VECTOR2(getCursorPosX(), getCursorPosY());
					//�n�_�ƏI�_����l�p�����							
					rightTop = { rightBottom.x,leftTop.y };
					leftBottom = { leftTop.x,rightBottom.y };

					//�ڕW�ƂȂ�l�p�̒��_��I�ԁi�l�p���������Ȃ��悤�ɂ���j
					//���オ�n�_�A�E�����I�_
					if (leftTop.x < rightBottom.x
						&& leftTop.y < rightBottom.y) {
						LT = leftTop;
						RB = rightBottom;
					}
					//�E�オ�n�_�A�������I�_
					if (leftTop.x > rightBottom.x
						&& leftTop.y < rightBottom.y) {
						LT = rightTop;
						RB = leftBottom;
					}
					//�������n�_�A�E�オ�I�_
					if (leftTop.x < rightBottom.x
						&& leftTop.y > rightBottom.y) {
						LT = leftBottom;
						RB = rightTop;
					}
					//�E�����n�_�A���オ�I�_
					if (leftTop.x > rightBottom.x
						&& leftTop.y > rightBottom.y) {
						LT = rightBottom;
						RB = leftTop;
					}

				}
				if (TRG_RELEASE(0) & PAD_TRG4) {//�}�E�X��
					//�n�_�ƏI�_����ł���l�p��������x�̑傫��
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


		//�N���b�N�����܂Ŏn�߂Ȃ�
		if (moveFlg == true) {
			if (vec2LengthSq(LT - mLeftTop) > 1
				|| vec2LengthSq(RB - mRightBottom) > 1) {
				//�w�肵���l�p�Ɍ�����
				mLeftTop += anyFlameArrive(40, speedLT, started, mLeftTop, LT);
				mRightBottom += anyFlameArrive(40, speedRB, started, mRightBottom, RB);
				//�n�_�ƏI�_����l�p�����
				mRightTop = { mRightBottom.x,mLeftTop.y };
				mLeftBottom = { mLeftTop.x,mRightBottom.y };


				//���߂̋������~�����̂ł��������[�v������ڂ��I�������Ƀt���O�𗧂Ă�
				started = true;
			}
			else {

				moveFlg = false;

				LT = {};
				RB = {};

				started = false;
				stayCount = 0;

				//����������
				if (pl->lHit)pl->speed.x = speedLT.x * 0.5;
				if (pl->rHit)pl->speed.x = speedRB.x * 0.5;
				if (pl->tHit)pl->speed.y = speedLT.y * 0.5;
				if (pl->bHit)pl->speed.y = speedRB.y * 0.5;


			}
		}
	}

	//�^�C�g�����
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
				//�w�肵���l�p�Ɍ�����
				mLeftTop += anyFlameArrive(40, speedLT, started, mLeftTop, LT);
				mRightBottom += anyFlameArrive(40, speedRB, started, mRightBottom, RB);
				//�n�_�ƏI�_����l�p�����
				mRightTop = { mRightBottom.x,mLeftTop.y };
				mLeftBottom = { mLeftTop.x,mRightBottom.y };


				//���߂̋������~�����̂ł��������[�v������ڂ��I�������Ƀt���O�𗧂Ă�
				started = true;
			}
			else {
				moveFlg = false;
				started = false;


				LT = {};
				RB = {};

				//����������
				if (pl->lHit)pl->speed.x = speedLT.x * 0.5;
				if (pl->rHit)pl->speed.x = speedRB.x * 0.5;
				if (pl->tHit)pl->speed.y = speedLT.y * 0.5;
				if (pl->bHit)pl->speed.y = speedRB.y * 0.5;

				if (toBtnFlg) {
					Title::instance()->changeScene(Game::instance());  // �Q�[���̃X�e�[�W�ɐ؂�ւ�
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

	//��
	data->draw(
		SCREEN_WIDTH / 2,
		mLeftTop.y,
		scale.x, scale.y,
		ToRadian(180)
	);
	//��
	data->draw(
		SCREEN_WIDTH / 2,
		mRightBottom.y,
		scale.x, scale.y,
		ToRadian(0)
	);
	//��
	data->draw(
		mLeftTop.x,
		SCREEN_HEIGHT / 2,
		scale.x, scale.y,
		ToRadian(90)
	);
	//�E
	data->draw(
		mRightBottom.x,
		SCREEN_HEIGHT / 2,
		scale.x, scale.y,
		ToRadian(270)
	);
}

//VECTOR2 Wall::arrive(VECTOR2& speed, VECTOR2 chacer, VECTOR2 target) {
//	VECTOR2 acc = vec2Normalize(target - chacer) * wallSpeed;
//	//���߂��x�N�g��������
//	speed += acc;
//	float dist = vec2Length(target - chacer);
//	if (dist > arriveDist) {
//		//����
//		if (vec2LengthSq(speed) > maxSpeed* maxSpeed) {
//			speed = vec2Normalize(speed) * maxSpeed;
//		}
//	}
//	else {
//		//�߂��܂ł���ƌ���
//		speed = vec2Normalize(speed) * maxSpeed * dist / arriveDist;
//	}
//	return speed;
//}


VECTOR2 Wall::anyFlameArrive(int moveFlame, VECTOR2& speed, bool started, VECTOR2 chacer, VECTOR2 target) {
	//moveFlame�Ŏw�肳�ꂽ�t���[������target�̏ꏊ�܂�chacer����������悤�ɓ�������֐�
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




