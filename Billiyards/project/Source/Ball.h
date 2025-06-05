#pragma once
#include "../Library/GameObject.h"


class Ball : public GameObject
{
public:
	Ball(int num, VECTOR3 pos);
	~Ball();
	void Update() override;
	void Draw() override;
private:
	int hImage;
	int number;
	VECTOR3 position; 
	VECTOR3 velocity; // ˆÚ“®—Ê

	int catchX, catchY;
	bool catched;
};

