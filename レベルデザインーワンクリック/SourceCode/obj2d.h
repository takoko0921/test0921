#ifndef INCLUDED_OBJ2D
#define	INCLUDED_OBJ2D
//******************************************************************************
//
//
//      OBJ2D�N���X
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include <list>
#include "../GameLib/vector.h"
#include "../GameLib/obj2d_data.h"

// �O���錾
class OBJ2D;

//==============================================================================

// �ړ��A���S���Y���N���X�i���ۃN���X�j
class MoveAlg
{
public:
    virtual void move(OBJ2D* obj) = 0;  // �������z�֐������̂ŁAMoveAlg�^�̃I�u�W�F�N�g�͐錾�ł��Ȃ��i�h�������Ďg���j
};

// �����A���S���Y���N���X�i���ۃN���X�j
class EraseAlg
{
public:
    virtual void erase(OBJ2D* obj) = 0; // ��Ɠ��l
};

//==============================================================================

//==============================================================================
//
//      OBJ2D�N���X
//
//==============================================================================

class OBJ2D
{
public:
    // �����o�ϐ�
    GameLib::SpriteData*    data = nullptr;               // �X�v���C�g�f�[�^									
	GameLib::Anime          anime = {};              // �A�j���[�V�����N���X

	VECTOR2                 position = {};           // �ʒu
    VECTOR2                 scale = {};              // �X�P�[��
    float                   angle = 0;              // �p�x
    VECTOR4                 color = {};              // �`��F
    VECTOR2                 size = {};               // ������p�T�C�Y�i�c���j

    MoveAlg*                mvAlg = nullptr;               // �ړ��A���S���Y��
    EraseAlg*               eraseAlg = nullptr;           // �����A���S���Y��

    float                   velocity = 0;           // ���x
    VECTOR2                 speed = {};              // �u�Ԃ̈ړ��ʃx�N�g��
    int                     state = 0;              // �X�e�[�g
    int                     timer = 0;              // �^�C�}�[

    GameLib::fRECT          hitRect = {};            // �����蔻��RECT

    bool                    judgeFlg = false;          // �����蔻��̗L���itrue:�L�� / false:�����j
    bool                    isDrawHitRect = false;      // �����蔻��`��t���O

    VECTOR2                 delta = {};              // �ړ��ʂ̍���


	GameLib::AnimeData* animeData = nullptr;    // �A�j���[�V�����f�[�^
	bool					onGround = false;

	bool					lHit = false;
	bool					rHit = false;
	bool					tHit = false;
	bool					bHit = false;


	

	int						stayCount = 0;

	bool					hitFlg = false;

	int						type = 0;
public:
    // �����o�֐�
    OBJ2D();        // �R���X�g���N�^
	void move();    // �ړ�
	void draw();    // �`��

	void drawHitRect(const VECTOR4&);           // �����蔻��`��

    bool animeUpdate();    // �A�j���[�V�����̃A�b�v�f�[�g
};

//==============================================================================

// OBJ2DManager�N���X
class OBJ2DManager
{
protected:
    std::list<OBJ2D>  objList; // ���X�g�iOBJ2D�̔z��̂悤�Ȃ��́j
public:
    // �f�X�g���N�^
    ~OBJ2DManager();

    void init();    // ������
    void update();  // �X�V
    void draw();    // �`��

    OBJ2D* add(MoveAlg* mvAlg, const VECTOR2& pos = VECTOR2(0, 0)); // objList�ɐV����OBJ2D��ǉ�����

	OBJ2D* addSpr(int type,GameLib::SpriteData* data,MoveAlg* mvAlg, const VECTOR2& pos = VECTOR2(0, 0)); // objList�ɐV����OBJ2D��ǉ�����
    std::list<OBJ2D>* getList() { return &objList; }                // objList���擾����
};

//******************************************************************************

#endif// ! INCLUDED_OBJ2D