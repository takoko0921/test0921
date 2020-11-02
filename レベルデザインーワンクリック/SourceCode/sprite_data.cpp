//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< データ >---------------------------------------------------------------
// 2D画像ロードデータ
LoadTexture loadTexture[] = {
	{ TEXNO::STR_TITLE,           L"./Data/Images/strayBox.png",           1U },
	{ TEXNO::BOTTON,           L"./Data/Images/botton.png",           1U },
	{ TEXNO::MOUSE,           L"./Data/Images/mouse.png",           1U },

	{ TEXNO::PLAYER,        L"./Data/Images/cardboard5.png",        1U },// プレイヤー
	{ TEXNO::MAP_TERRAIN,   L"./Data/Maps/terrain_chip.png",    336U }, // マップ地形

	{ TEXNO::SWITCH,           L"./Data/Images/switch.png",           1U },   // SWITCH
	{ TEXNO::SPR_GOAL,           L"./Data/Images/rift.png",           1U },
	{ TEXNO::WALL,           L"./Data/Images/wall.png",           1U },
	{ TEXNO::BACK,           L"./Data/Images/back.png",           1U },
	{ -1, nullptr }	// 終了フラグ
};

//------< マクロ >--------------------------------------------------------------
#define SPRITE_LEFT_TOP(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),0,0  }  // 画像の頭が中心
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // 画像の足元が中心
#define SPRITE_TOP(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,0  }  // 画像の頭が中心
//------< プレイヤー >----------------------------------------------------------
//SpriteData sprPlayer = SPRITE_BOTTOM(TEXNO::PLAYER, 0,0, 48,32);
SpriteData sprTitle = SPRITE_LEFT_TOP(TEXNO::STR_TITLE,  0, 0, 561, 240);

SpriteData sprBotton0 = SPRITE_CENTER(TEXNO::BOTTON, 0, 48 * 0, 288, 48);
SpriteData sprBotton1 = SPRITE_CENTER(TEXNO::BOTTON, 0, 48*1, 288, 48);
SpriteData sprBotton2 = SPRITE_CENTER(TEXNO::BOTTON, 0, 48 * 2, 288, 48);

SpriteData sprPlayer = SPRITE_BOTTOM(TEXNO::PLAYER, 0, 0, 50, 34);

SpriteData sprMouse0 = SPRITE_TOP(TEXNO::MOUSE, 32*0, 0, 32, 48);
SpriteData sprMouse1 = SPRITE_TOP(TEXNO::MOUSE, 32 * 1, 0, 32, 48);
////RED
//ue
SpriteData sprSwitch_Red_Up1 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 0, 32 * 0, 32, 32);
SpriteData sprSwitch_Red_Up2 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 4, 32 * 0, 32, 32);
//migi
SpriteData sprSwitch_Red_Right1 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 1, 32 * 0, 32, 32);
SpriteData sprSwitch_Red_Right2 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 5, 32 * 0, 32, 32);
//sita
SpriteData sprSwitch_Red_Down1 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 2, 32 * 0, 32, 32);
SpriteData sprSwitch_Red_Down2 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 6, 32 * 0, 32, 32);
//hidari
SpriteData sprSwitch_Red_Left1 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 3, 32 * 0, 32, 32);
SpriteData sprSwitch_Red_Left2 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 7, 32 * 0, 32, 32);

////GREEN
//ue
SpriteData sprSwitch_Green_Up1 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 0, 32 * 1, 32, 32);
SpriteData sprSwitch_Green_Up2 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 4, 32 * 1, 32, 32);
//migi
SpriteData sprSwitch_Green_Right1 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 1, 32 * 1, 32, 32);
SpriteData sprSwitch_Green_Right2 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 5, 32 * 1, 32, 32);
//sita
SpriteData sprSwitch_Green_Down1 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 2, 32 * 1, 32, 32);
SpriteData sprSwitch_Green_Down2 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 6, 32 * 1, 32, 32);
//hidari
SpriteData sprSwitch_Green_Left1 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 3, 32 * 1, 32, 32);
SpriteData sprSwitch_Green_Left2 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 7, 32 * 1, 32, 32);

////BLUE
//ue
SpriteData sprSwitch_Blue_Up1 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 0, 32 * 2, 32, 32);
SpriteData sprSwitch_Blue_Up2 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 4, 32 * 2, 32, 32);
//migi
SpriteData sprSwitch_Blue_Right1 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 1, 32 * 2, 32, 32);
SpriteData sprSwitch_Blue_Right2 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 5, 32 * 2, 32, 32);
//sita
SpriteData sprSwitch_Blue_Down1 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 2, 32 * 2, 32, 32);
SpriteData sprSwitch_Blue_Down2 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 6, 32 * 2, 32, 32);
//hidari
SpriteData sprSwitch_Blue_Left1 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 3, 32 * 2, 32, 32);
SpriteData sprSwitch_Blue_Left2 = SPRITE_CENTER(TEXNO::SWITCH, 32 * 7, 32 * 2, 32, 32);

SpriteData sprGoal1 = SPRITE_CENTER(TEXNO::SPR_GOAL, 224 * 0, 114 * 0, 224, 114);
SpriteData sprGoal2 = SPRITE_CENTER(TEXNO::SPR_GOAL, 224 * 1, 114 * 0, 224, 114);
SpriteData sprGoal3 = SPRITE_CENTER(TEXNO::SPR_GOAL, 224 * 2, 114 * 0, 224, 114);
SpriteData sprGoal4 = SPRITE_CENTER(TEXNO::SPR_GOAL, 224 * 3, 114 * 0, 224, 114);
SpriteData sprGoal5 = SPRITE_CENTER(TEXNO::SPR_GOAL, 224 * 0, 114 * 1, 224, 114);
SpriteData sprGoal6 = SPRITE_CENTER(TEXNO::SPR_GOAL, 224 * 1, 114 * 1, 224, 114);
SpriteData sprGoal7 = SPRITE_CENTER(TEXNO::SPR_GOAL, 224 * 2, 114 * 1, 224, 114);
SpriteData sprGoal8 = SPRITE_CENTER(TEXNO::SPR_GOAL, 224 * 3, 114 * 1, 224, 114);

SpriteData sprWall = SPRITE_TOP(TEXNO::WALL, 0, 0, 250, 24);

SpriteData sprBack = SPRITE_CENTER(TEXNO::BACK, 0, 0, 48, 32);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
