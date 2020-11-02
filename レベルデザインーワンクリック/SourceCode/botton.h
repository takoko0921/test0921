#pragma once

class Botton : public MoveAlg
{
public:
	void move(OBJ2D* obj);
};

// 移動アルゴリズムの実体
EXTERN Botton botton;


// 消去アルゴリズム
class EraseBotton: public EraseAlg
{
	void erase(OBJ2D* obj);
};

// 消去アルゴリズムの実体
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