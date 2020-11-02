#ifndef INCLUDED_TITLE
#define	INCLUDED_TITLE

//******************************************************************************
//
//
//      �^�C�g���V�[��
//
//
//******************************************************************************

//==============================================================================
//
//      Title�N���X
//
//==============================================================================

class Title : public Scene
{
public:
    static Title* instance() { return &instance_; }

	void init();
	void update();
	void draw();
	void uninit();

	PlayerManager* playerManager() { return playerManager_; }
	Wall* wallManager() { return wallManager_; }
	BottonManager* bottonManager() { return bottonManager_; }

private:
    static Title instance_;

	PlayerManager* playerManager_;
	Wall* wallManager_;
	BottonManager* bottonManager_;
};

//******************************************************************************

#endif // !INCLUDED_TITLE
