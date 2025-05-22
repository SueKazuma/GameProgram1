#pragma once
#include "Object3D.h"

class Coin : public Object3D
{
public:
	Coin(VECTOR pos);
	~Coin();
	void Update() override;
private:
	bool gotten; // ���ꂽ��
	void homingStart();
	void homingUpdate();
	VECTOR3 velocity; // �ړ��x�N�g��
};