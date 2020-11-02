#pragma once
class Switch : public MoveAlg
{
public:

	void move(OBJ2D* obj);


};
EXTERN Switch mapObj;

class EraseSwitch : public EraseAlg
{
public:
	void erase(OBJ2D* obj);
};
EXTERN EraseSwitch eraseSwitch;

class Goal : public MoveAlg
{
public:

	void move(OBJ2D* obj);


};
EXTERN Goal goal;

class EraseGoal : public EraseAlg
{
public:
	void erase(OBJ2D* obj);
};
EXTERN EraseGoal eraseGoal;

class MapObjManager : public OBJ2DManager
{


	std::list<OBJ2DManager*> managerList;
public:
	enum TYPE {
		UP = 0,
		RIGHT,
		DOWN,
		LEFT,
		STAND,

		GOAL,
	};

	// マップチップのインデックス
	enum BOTTAN_INDEX {


		GOAL_INDEX = 2,


		//RED
		RED_UP_INDEX = 8,
		RED_RIGHT_INDEX,
		RED_DOWN_INDEX,
		RED_LEFT_INDEX,

		//GREEN
		GREEN_UP_INDEX = 17,
		GREEN_RIGHT_INDEX,
		GREEN_DOWN_INDEX,
		GREEN_LEFT_INDEX,
		//BLUE
		BLUE_UP_INDEX = 25,
		BLUE_RIGHT_INDEX,
		BLUE_DOWN_INDEX,
		BLUE_LEFT_INDEX,


	};

	void init(char[][BG::CHIP_NUM_X]);
	std::list<OBJ2DManager*>* getManagerList() { return &managerList; }

	//複数回使うので省略する為の関数
	OBJ2D* aAddSpr(int type, GameLib::SpriteData* data, MoveAlg* mvAlg, const VECTOR2& pos = VECTOR2(0, 0)) {
		return addSpr(type, data, mvAlg, VECTOR2(static_cast<float>(pos.x * BG::CHIP_SIZE),
			static_cast<float>(pos.y * BG::CHIP_SIZE)));
	}


};