#pragma once
#include "Object3D.h"
class Coin : public Object3D
{
public:
	Coin(VECTOR pos);
	~Coin();
	void Update() override;
private:
	bool gotten; // ‚Æ‚ç‚ê‚¿‚á‚Á‚½
	void homingStart();
	void homingUpdate();
	VECTOR3 velocity; // ˆÚ“®ƒxƒNƒgƒ‹
};

