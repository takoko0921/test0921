#pragma once
//******************************************************************************
//
//
//      Judge
//
//
//******************************************************************************

//------< �C���N���[�h >----------------------------------------------------------

// �����蔻��֐�
void judge();

// ��`�����蔻��
bool rectHitCheck(const GameLib::fRECT&, const GameLib::fRECT&);

// OBJ2D���m�̂����蔻��
bool judgeCheck(const OBJ2D&, const OBJ2D&, float margin = 0);
bool judgeCheck2(const OBJ2D&, const OBJ2D&);
