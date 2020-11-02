#ifndef INCLUDED_GAME
#define	INCLUDED_GAME

//******************************************************************************
//
//
//      �Q�[���V�[��
//
//
//******************************************************************************

//==============================================================================
//
//      Game�N���X
//
//==============================================================================

class Game : public Scene
{

public:
    static Game* instance() { return &instance_; }

    void init();
    void update();
    void draw();
    void uninit();

	void setState(int num) { state = num; }


    // �Q�b�^�[�͌���_�����Ȃ�
	BG* bgManager() { return bgManager_; }
    PlayerManager*      playerManager()     { return playerManager_; }
	Wall*				wallManager()		{ return wallManager_; }
	MapObjManager* mapObjManager() { return bottanManager_; }
	

	int stage = 0;

private:
    bool                isPaused;



    // �����o�ϐ��͌���_������
	BG* bgManager_;
    PlayerManager*      playerManager_;
	Wall*				wallManager_;
	MapObjManager* bottanManager_;
	//���Ŏg��Ȃ��̂�manager�͂���Ȃ�
	Tutorial* tutorail;

    static Game instance_;
};

//******************************************************************************

#endif // !INCLUDED_GAME
