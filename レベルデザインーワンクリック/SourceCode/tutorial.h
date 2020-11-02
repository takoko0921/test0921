#pragma once
class Tutorial {
	VECTOR2 anyFlameArrive(int moveFlame, VECTOR2& speed,bool started, VECTOR2 chacer, VECTOR2 target);
public:
	GameLib::SpriteData* data = &sprMouse0;

	VECTOR2                 pos = {400,400};
	VECTOR2                 speed = { 0,0 };
	

	VECTOR2					leftTop = { 0,0 };
	VECTOR2					rightTop = { 960,0 };
	VECTOR2					leftBottom = { 0,640 };
	VECTOR2					rightBottom = { 960,640 };

	int						stayCount = 0;
	bool					clicked = false;
	bool					started = false;
	bool					inputFlg = false;
	int						count = 0;
	int						state = 0;


	void update();
	void draw();
};