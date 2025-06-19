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
	VECTOR3 velocity; // �ړ���
	VECTOR3 addVelocity; // �ǉ��ړ��ʁi���velocity�ɑ����j

	int catchX, catchY;
	bool catched;
};

