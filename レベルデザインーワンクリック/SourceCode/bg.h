#ifndef INCLUDED_BG
#define INCLUDED_BG

//******************************************************************************
//
//
//      bg.h
//
//
//******************************************************************************

//==============================================================================
//
//      BG�N���X
//
//==============================================================================

class BG
{
public:
    //------< �萔 >------------------------------------------------------------
    static const int CHIP_NUM_X = 30;                       // �}�b�v�̉������̃`�b�v��
    static const int CHIP_NUM_Y = 20;                       // �}�b�v�̏c�����̃`�b�v��
    static const int CHIP_SIZE = 32;                        // %���Z�q���g�p���邽��int�^���g�p����
    static const int CHIP_NUM_PER_LINE = 8;                 // �}�b�v�`�b�v��1��8��
    static const int CHIP_LINE_NUM = 4;                     // �}�b�v�`�b�v���S�s

    static constexpr float WIDTH = static_cast<float>(CHIP_NUM_X * CHIP_SIZE);  // �}�b�v�̕��i�h�b�g�j
    static constexpr float HEIGHT = static_cast<float>(CHIP_NUM_Y * CHIP_SIZE); // �}�b�v�̍����i�h�b�g�j
    static constexpr float SCROLL_MERGIN_X = 120.f;         // ���̐��l����ʒ[�ɋ߂Â�����X�N���[������i���j
    static constexpr float SCROLL_MERGIN_Y = 80.f;          // ���̐��l����ʒ[�ɋ߂Â�����X�N���[������i�c�j
    static constexpr float ADJUST_Y = 0.125f;               // �����蔻��ł̈ʒu�����p�i�c�j
    static constexpr float ADJUST_X = 0.0125f;              // �����蔻��ł̈ʒu�����p�i���j

    // �n�`�iTerrain�j�̑���
    enum TR_ATTR
    {
        TR_NONE = -1,   // -1:�����Ȃ�
        ALL_BLOCK,      //  0:�l���u���b�N
        UPPER_BLOCK,    //  1:�ゾ���u���b�N
        HASHIGO,        //  2:�͂���
		NEEDLE,
    };

    // �w�i�iBack�j�̑���
    enum BG_ATTR
    {
        BG_NONE = -1,   // -1:�����Ȃ�
        NORMAL,         //  0:���ʁi���ɉ����Ȃ��j
        WATER,          //  1:�����i��R���󂯂�j
		
    };

	int stage = 2;

private:
    // �n�`�`�b�v�e�N�X�`���̊e�����̑������`����
    const TR_ATTR terrainAttr[CHIP_LINE_NUM][CHIP_NUM_PER_LINE] = {
        { ALL_BLOCK,   ALL_BLOCK,   ALL_BLOCK,   ALL_BLOCK,    NEEDLE,		 NEEDLE,		NEEDLE,	   NEEDLE,},
        { UPPER_BLOCK, UPPER_BLOCK, UPPER_BLOCK, UPPER_BLOCK,TR_NONE, ALL_BLOCK, ALL_BLOCK, ALL_BLOCK,	 },
        { HASHIGO,     HASHIGO,     TR_NONE,     TR_NONE,     TR_NONE,   TR_NONE,   TR_NONE,   TR_NONE,  },
		 { HASHIGO,     HASHIGO,     TR_NONE,     TR_NONE,     TR_NONE,   TR_NONE,   TR_NONE,   TR_NONE,  },
    };

    // �w�i�`�b�v�e�N�X�`���̊e�����̑������`����
    const BG_ATTR bgAttr[CHIP_LINE_NUM][CHIP_NUM_PER_LINE] = {
        { NORMAL,      NORMAL,      NORMAL,      NORMAL,      NORMAL,    NORMAL,    BG_NONE,   BG_NONE, },
        { WATER,       WATER,       WATER,       WATER,       BG_NONE,   BG_NONE,   BG_NONE,   BG_NONE, },
        { BG_NONE,     BG_NONE,     BG_NONE,     BG_NONE,     BG_NONE,   BG_NONE,   BG_NONE,   BG_NONE, },
        { BG_NONE,     BG_NONE,     BG_NONE,     BG_NONE,     BG_NONE,   BG_NONE,   BG_NONE,   BG_NONE, },
    };

    //------< �ϐ� >------------------------------------------------------------
    VECTOR2 scroll;                                         // ���ݕ\������Ă��鍶��̒n�_�̍��W

    char back[CHIP_NUM_Y][CHIP_NUM_X];                      // �w�i�f�[�^
    char terrain[CHIP_NUM_Y][CHIP_NUM_X];                   // �n�`�f�[�^

public:
    BG();
    ~BG();

    // ������
    void init();

    // �X�V
    void update();

    // �`��
    void drawBack();                                        // �w�i�`��
    void drawTerrain();                                     // �n�`�`��

    // �X�N���[���ʒu�擾
    float getScrollX() { return scroll.x; }
    float getScrollY() { return scroll.y; }
    const VECTOR2& getScrollPos() { return scroll; }

    // �����蔻��
    // ������
    bool isFloor(float, float, float);          // ���ɂ߂荞��ł��邩
    void mapHoseiDown(OBJ2D*);                  // �������␳����

    // �����
    bool isCeiling(float, float, float);        // �V��ɂ������Ă��邩
    void mapHoseiUp(OBJ2D*);                    // ������␳����

    // ������
    bool isWall(float, float, float);           // �������ɕǂɂ߂荞��ł��邩
    void mapHoseiRight(OBJ2D*);                 // �E�����␳����
    void mapHoseiLeft(OBJ2D*);                  // �������␳����


	//�͂�ɑ΂��鏈��
	bool BG::isNeedle(float x, float y, float width,float height);

	char(*getTerrain())[BG::CHIP_NUM_X]{ return terrain; }
private:
    // �N���A
    void clear();

    // �}�b�v�f�[�^�̃��[�h
    bool loadMapData(const char[CHIP_NUM_Y][CHIP_NUM_X], char[CHIP_NUM_Y][CHIP_NUM_X]);

    // BG�ATerrain���ʂ̕`��֐�
    void draw(int, char[CHIP_NUM_Y][CHIP_NUM_X]);  // �`�揈���i�X���[�Y�ȃX�N���[���j

    // �}�b�v�X�N���[���p
    void scrollMap();

    bool isHitDown(float, float);
    bool isHitAll(float, float);
    bool isUpperQuater(float);
    TR_ATTR getTerrainAttr(float, float);
    int getData(char[CHIP_NUM_Y][BG::CHIP_NUM_X], float, float);
};

//******************************************************************************

#endif // ! INCLUDED_BG
