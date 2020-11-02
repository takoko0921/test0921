#pragma once
//******************************************************************************
//
//
//      Judge
//
//
//******************************************************************************

//------< インクルード >----------------------------------------------------------

// あたり判定関数
void judge();

// 矩形あたり判定
bool rectHitCheck(const GameLib::fRECT&, const GameLib::fRECT&);

// OBJ2D同士のあたり判定
bool judgeCheck(const OBJ2D&, const OBJ2D&, float margin = 0);
bool judgeCheck2(const OBJ2D&, const OBJ2D&);
