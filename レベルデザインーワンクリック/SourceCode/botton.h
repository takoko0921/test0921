#pragma once

class Botton : public MoveAlg
{
public:
	void move(OBJ2D* obj);
};

// �ړ��A���S���Y���̎���
EXTERN Botton botton;


// �����A���S���Y��
class EraseBotton: public EraseAlg
{
	void erase(OBJ2D* obj);
};

// �����A���S���Y���̎���
EXTERN EraseBotton      erasebotton;

class BottonManager : public OBJ2DManager
{
public:
	enum TYPE {
		STAGE0 = 0,
		STAGE1,
		STAGE2,
	};
};