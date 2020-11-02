#include "all.h"
using namespace GameLib;

void Tutorial::update() {
	using namespace input;
	if (STATE(0) & PAD_TRG4) {
		inputFlg = true;
		state = 0;
	}
	if (TRG_RELEASE(0) & PAD_TRG4) {
		inputFlg = false;
	}

	switch (state) {
	case 0:

		
		data = nullptr;
		stayCount++;

		if (stayCount == 40) {

			stayCount = 0;
			state++;
		}
		break;
	case 1:
		pos = { 400,400 };
		data = &sprMouse0;
		stayCount++;

		if (stayCount == 40) {
			clicked = true;
			leftBottom = pos;
			rightTop = pos;
			leftTop = pos;
			rightBottom = pos;

			stayCount = 0;
			state++;
		}
		break;
	case 2:
		data = &sprMouse1;
		stayCount++;

		if (stayCount == 40) {
			stayCount = 0;
			state++;
		}
		break;
		{
	case 3:
		VECTOR2 target = { 700,200 };
		pos += anyFlameArrive(30, speed, started, pos, target);
		started = true;
		rightTop = pos;
		//始点と終点から四角を作る
		leftTop = {leftBottom.x,rightTop.y};
		rightBottom = {rightTop.x,leftBottom.y};

		if (vec2LengthSq(target - pos) < 1) {
			state++;
		}
		break;
		}

	case 4:
		stayCount++;

		if (stayCount == 40) {
			stayCount = 0;
			state=0;
			clicked = false;

			leftTop = { 0,0 };
			rightTop = { 960,0 };
			leftBottom = { 0,640 };
			rightBottom = { 960,640 };
		}
		break;

	}

}

void Tutorial::draw() {
	
	if (!inputFlg) {
		if (Game::instance()->wallManager()->moveFlg == false) {
			VECTOR4 col = { 1,1,1,1 };

			if (clicked) {
				primitive::circle(leftTop, 10, col);
				primitive::circle(rightTop, 10, col);
				primitive::circle(leftBottom, 10, col);
				primitive::circle(rightBottom, 10, col);

				primitive::line(leftTop, rightTop, col);
				primitive::line(leftBottom, rightBottom, col);
				primitive::line(leftTop, leftBottom, col);
				primitive::line(rightTop, rightBottom, col);
			}

			if (data != nullptr) {
				data->draw(pos);
			}
		}

	}

}

VECTOR2 Tutorial::anyFlameArrive(int moveFlame, VECTOR2& speed, bool started, VECTOR2 chacer, VECTOR2 target) {
	//moveFlameで指定されたフレーム分でtargetの場所までchacerが到着するように動かせる関数
	if (!started) {
		VECTOR2 toTarget = target - chacer;
		speed = toTarget / moveFlame;
	}
	if(vec2LengthSq(target-chacer)> 1){
		return speed;
	}
	else {
		return {};
	}

}