#pragma once
#include "../Library/GameObject.h"


class Ball : public GameObject
{
public:
	Ball(int num, VECTOR3 pos);
	~Ball();
	void Update() override;
	void Draw() override;
	VECTOR3 GetPosition() { return position; }
	void AddForce(VECTOR3 force);
	void HitOtherBall(Ball* other);
private:
	int hImage;
	int number;
	VECTOR3 position; 
	VECTOR3 velocity; // 移動量
	VECTOR3 addVelocity; // 追加移動量（後でvelocityに足す）

	int catchX, catchY;
	bool catched;
};

