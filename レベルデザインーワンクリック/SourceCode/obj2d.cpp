//******************************************************************************
//
//
//      OBJ2D�N���X
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------
#include "all.h"

using namespace GameLib;

//--------------------------------------------------------------
//  �R���X�g���N�^
//--------------------------------------------------------------
OBJ2D::OBJ2D()
{

    scale = VECTOR2(1, 1);          // �������Y�ꂪ�����悤�Ɂi�X�P�[���[���Ȃ牽���\������Ȃ��j
    color = VECTOR4(1, 1, 1, 1);    // �������Y�ꂪ�����悤�Ɂi�s�����x�[���Ȃ牽���\������Ȃ��j
}


//--------------------------------------------------------------
//  �ړ�
//--------------------------------------------------------------
void OBJ2D::move()
{
    if (mvAlg) mvAlg->move(this);                   // �ړ��A���S���Y�������݂���΁Amove���\�b�h���Ă�
    if (eraseAlg) eraseAlg->erase(this);            // �����A���S���Y�������݂���΁Aerase���\�b�h���Ă�
}

//--------------------------------------------------------------
//  �`��
//--------------------------------------------------------------
void OBJ2D::draw()
{
    if (data)
    {
        data->draw(position, 
            scale, angle, color);  // data��draw���\�b�h�ŃX�v���C�g��`�悷��
    }
}

//--------------------------------------------------------------
//  �A�j���[�V�����X�V
//--------------------------------------------------------------
//  �߂�l�Ftrue  �A�j�����擪�ɖ߂�u��
//        :false ����ȊO
//--------------------------------------------------------------
bool OBJ2D::animeUpdate()
{
	if (animeData == nullptr)
	{
		return false;
	}

    if (anime.pPrev != animeData)           // �A�j���f�[�^���؂�ւ�����Ƃ�
    {
        anime.pPrev = animeData;
        anime.patNum = 0;	                // �擪����Đ�
        anime.frame = 0;
    }

    animeData += anime.patNum;
    data = animeData->data;                 // ���݂̃p�^�[���ԍ��ɊY������摜��ݒ�

    anime.frame++;
    if (anime.frame >= animeData->frame)    // �ݒ�t���[�����\��������
    {
        anime.frame = 0;
        anime.patNum++;                     // ���̃p�^�[����
        if ((animeData + 1)->frame < 0)     // �I���R�[�h�̂Ƃ�
        {
            anime.patNum = 0;               // �擪�֖߂�
            return true;
        }
    }

    return false;
}

//******************************************************************************
//
//
//      OBJ2DManager�N���X
//
//
//******************************************************************************

//--------------------------------------------------------------
//  ������
//--------------------------------------------------------------
void OBJ2DManager::init()
{
    //���X�g��OBJ2D��S�ăN���A����
    objList.clear();
}

//--------------------------------------------------------------
//  ���X�g�֒ǉ�
//--------------------------------------------------------------
OBJ2D* OBJ2DManager::add(MoveAlg* mvAlg, const VECTOR2& pos)
{
    OBJ2D obj;                          // OBJ2D��錾����
    obj.mvAlg = mvAlg;                  // mvAlg�Ɉ�����mvalg����
    obj.position = pos;                 // position�Ɉ�����pos����
    obj.scale = VECTOR2(1, 1);          // �X�P�[���͓��{
    obj.color = VECTOR4(1, 1, 1, 1);    // �F�͔��i�s�����x1.0f�j

    objList.push_back(obj);             // ���X�g��obj��ǉ�����
    return &(*objList.rbegin());        // ���ǉ�����obj�̃A�h���X��Ԃ��i�����Ŏg����悤�Ɂj
}

OBJ2D* OBJ2DManager::addSpr(int type, GameLib::SpriteData* sprData, MoveAlg* mvAlg, const VECTOR2& pos)
{
	OBJ2D obj;                          // OBJ2D��錾����

	obj.type = type;
	obj.data = sprData;
	obj.mvAlg = mvAlg;                  // mvAlg�Ɉ�����mvalg����
	obj.position = pos;                 // position�Ɉ�����pos����
	obj.scale = VECTOR2(1, 1);          // �X�P�[���͓��{
	obj.color = VECTOR4(1, 1, 1, 1);    // �F�͔��i�s�����x1.0f�j

	objList.push_back(obj);             // ���X�g��obj��ǉ�����
	return &(*objList.rbegin());        // ���ǉ�����obj�̃A�h���X��Ԃ��i�����Ŏg����悤�Ɂj
}

//--------------------------------------------------------------
//  �����蔻��̉���
//--------------------------------------------------------------
void OBJ2D::drawHitRect(const VECTOR4& col)
{
	/*primitive::rect(
		VECTOR2(hitRect.left - Game::instance()->bgManager()->getScrollX(),
			hitRect.top - Game::instance()->bgManager()->getScrollY()),
		VECTOR2(hitRect.right - hitRect.left, hitRect.bottom - hitRect.top),
		VECTOR2(0, 0), 0,
		col);*/
}

//--------------------------------------------------------------
//  �X�V
//--------------------------------------------------------------
void OBJ2DManager::update()
{
    // �ړ�
    for (auto& it : objList)            // objList�̑S�Ă̗v�f�����[�v���Ait�Ƃ������O�Ŋe�v�f�ɃA�N�Z�X
    {
        it.move();                      // it��move���\�b�h���Ă�
    }

    // ��m�[�h�̍폜
    auto it = objList.begin();
    while (it != objList.end())
    {
        if (it->mvAlg)
        {
            it++;
        }
        else
        {
            it = objList.erase(it);
        }
    }
}

//--------------------------------------------------------------
//  �`��
//--------------------------------------------------------------
void OBJ2DManager::draw()
{
    for (auto& it : objList)            // objList�̑S�Ă̗v�f�����[�v���Ait�Ƃ������O�Ŋe�v�f�ɃA�N�Z�X 
    {
        it.draw();                      // it��draw���\�b�h���Ă�

		/*if (it.isDrawHitRect) {
			it.drawHitRect(VECTOR4(1.0f, 0.0f, 0.0f, 0.4f));
		}*/
    }
}

//--------------------------------------------------------------
//  �f�X�g���N�^
//--------------------------------------------------------------
OBJ2DManager::~OBJ2DManager()
{
    //���X�g��OBJ2D��S�ăN���A����
   // objList.clear();
}
