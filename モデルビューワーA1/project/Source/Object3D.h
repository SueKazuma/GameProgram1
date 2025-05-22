#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// ÉJÉÅÉâ
/// </summary>

class Object3D : public GameObject
{
public:
	Object3D();
	virtual ~Object3D();
	virtual void Update() override;
	virtual void Draw() override;
protected:
	int hModel;
	VECTOR rotation;
	VECTOR position;
};