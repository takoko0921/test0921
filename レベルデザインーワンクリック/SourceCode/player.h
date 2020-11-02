#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER

//******************************************************************************
//
//
//      Player.h
//
//
//******************************************************************************

//==============================================================================
//
//      �ړ��A���S���Y��
//
//==============================================================================

// �v���C���[����N���X
class Player : public MoveAlg
{
	void gravity(OBJ2D* obj);
	void againstWall(OBJ2D* obj);
	void againstMapChip(OBJ2D* obj);
	void areaCheck(OBJ2D* obj);
	void deceleration(OBJ2D* obj);


public:
	// �萔�i�����͂��̊֐����ł����g�p���Ȃ����߁A�����Ő錾���Ă���j
	static constexpr float KASOKU = 0.2f;     // �������E�c�����̉����x
	static constexpr float SPEED_MAX_Y = 7.0f;     // �ő�̗������x


    void move(OBJ2D* obj);


};

// �ړ��A���S���Y���̎���
EXTERN Player player;


// �����A���S���Y��
class ErasePlayer : public EraseAlg
{
    void erase(OBJ2D* obj);
};

// �����A���S���Y���̎���
EXTERN ErasePlayer      erasePlayer;

class PlayerManager : public OBJ2DManager
{
public:
};


#endif // !INCLUDED_PLAYER
