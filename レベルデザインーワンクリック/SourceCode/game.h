#ifndef INCLUDED_GAME
#define	INCLUDED_GAME

//******************************************************************************
//
//
//      ゲームシーン
//
//
//******************************************************************************

//==============================================================================
//
//      Gameクラス
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


    // ゲッターは後ろに_をつけない
	BG* bgManager() { return bgManager_; }
    PlayerManager*      playerManager()     { return playerManager_; }
	Wall*				wallManager()		{ return wallManager_; }
	MapObjManager* mapObjManager() { return bottanManager_; }
	

	int stage = 0;

private:
    bool                isPaused;



    // メンバ変数は後ろに_をつける
	BG* bgManager_;
    PlayerManager*      playerManager_;
	Wall*				wallManager_;
	MapObjManager* bottanManager_;
	//他で使わないのでmanagerはいらない
	Tutorial* tutorail;

    static Game instance_;
};

//******************************************************************************

#endif // !INCLUDED_GAME
