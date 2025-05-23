#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// カメラ
/// </summary>

class Camera : public GameObject
{
public:
	Camera();
	~Camera();
	void Update() override;
	void Draw() override;
private:
	VECTOR rotation;
	float distance; // カメラの距離
};