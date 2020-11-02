#ifndef INCLUDED_SPRITE_DATA
#define INCLUDED_SPRITE_DATA
//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

#include "../GameLib/texture.h"

// ラベル定義
enum TEXNO
{
	STR_TITLE,
	BOTTON,

	MOUSE,
    // ゲーム
    PLAYER,
    MAP_BACK,
    MAP_TERRAIN,

	SWITCH,
	SPR_GOAL,
	WALL,
	BACK,
};

extern GameLib::LoadTexture loadTexture[];


extern GameLib::SpriteData sprTitle;

extern GameLib::SpriteData sprBotton0;
extern GameLib::SpriteData sprBotton1;
extern GameLib::SpriteData sprBotton2;

//プレイヤー
extern GameLib::SpriteData sprPlayer;

extern GameLib::SpriteData sprMouse0;
extern GameLib::SpriteData sprMouse1;

//mapObj
////RED
//ue
extern GameLib::SpriteData sprSwitch_Red_Up1;
extern GameLib::SpriteData sprSwitch_Red_Up2;
//migi
extern GameLib::SpriteData sprSwitch_Red_Right1;
extern GameLib::SpriteData sprSwitch_Red_Right2;
//sita
extern GameLib::SpriteData sprSwitch_Red_Down1;
extern GameLib::SpriteData sprSwitch_Red_Down2;
//hidari
extern GameLib::SpriteData sprSwitch_Red_Left1;
extern GameLib::SpriteData sprSwitch_Red_Left2;

////GREEN
//ue
extern GameLib::SpriteData sprSwitch_Green_Up1;
extern GameLib::SpriteData sprSwitch_Green_Up2;
//migi
extern GameLib::SpriteData sprSwitch_Green_Right1;
extern GameLib::SpriteData sprSwitch_Green_Right2;
//sita
extern GameLib::SpriteData sprSwitch_Green_Down1;
extern GameLib::SpriteData sprSwitch_Green_Down2;
//hidari
extern GameLib::SpriteData sprSwitch_Green_Left1;
extern GameLib::SpriteData sprSwitch_Green_Left2;

////BLUE
//ue
extern GameLib::SpriteData sprSwitch_Blue_Up1;
extern GameLib::SpriteData sprSwitch_Blue_Up2;
//migi
extern GameLib::SpriteData sprSwitch_Blue_Right1;
extern GameLib::SpriteData sprSwitch_Blue_Right2;
//sita
extern GameLib::SpriteData sprSwitch_Blue_Down1;
extern GameLib::SpriteData sprSwitch_Blue_Down2;
//hidarii
extern GameLib::SpriteData sprSwitch_Blue_Left1;
extern GameLib::SpriteData sprSwitch_Blue_Left2;


extern GameLib::SpriteData sprGoal1;
extern GameLib::SpriteData sprGoal2;
extern GameLib::SpriteData sprGoal3;
extern GameLib::SpriteData sprGoal4;
extern GameLib::SpriteData sprGoal5;
extern GameLib::SpriteData sprGoal6;
extern GameLib::SpriteData sprGoal7;
extern GameLib::SpriteData sprGoal8;

extern GameLib::SpriteData sprWall;

extern GameLib::SpriteData sprBack;
#endif// ! INCLUDED_SPRITE_DATA
