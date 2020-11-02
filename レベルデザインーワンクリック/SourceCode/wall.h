#pragma once

class Wall {


	VECTOR2 arrive(VECTOR2& speed, VECTOR2 chacer, VECTOR2 target);
	VECTOR2 anyFlameArrive(int moveFlame, VECTOR2& speed, bool started, VECTOR2 chacer, VECTOR2 target);

public:

	float wallSpeed = 3.0f;
	float maxSpeed = 8.0f;
	float arriveDist = 100;

	GameLib::SpriteData* data = &sprWall;
	VECTOR2                 size = { 250 / 2,24 / 2 };
	VECTOR2                 scale = { 4,4 };

	bool					lHit = false;
	bool					rHit = false;
	bool					tHit = false;
	bool					bHit = false;


	VECTOR2					leftTop = { 0,0 };
	VECTOR2					rightTop = { 960,0 };
	VECTOR2					leftBottom = { 0,640 };
	VECTOR2					rightBottom = { 960,640 };

	VECTOR2					LT = {};
	VECTOR2					RB = {};

	VECTOR2					mLeftTop = { 0,0 };
	VECTOR2					mRightTop = { 960,0 };
	VECTOR2					mLeftBottom = { 0,640 };
	VECTOR2					mRightBottom = { 960,640 };

	bool					moveFlg = false;
	bool					clicked = false;

	VECTOR2					speedLT = {};
	VECTOR2					speedRB = {};

	int						stayCount = 0;
	bool					started = false;

	bool					toBtnFlg = false;

	void update();
	void draw();
};