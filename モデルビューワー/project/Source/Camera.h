#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// �J����
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
	float distance; // �J�����̋���
};