#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// ���W�� �Q�[���I�u�W�F�N�g
/// 
/// X,Y,Z�̍��W����\������
/// </summary>

class Axis : public GameObject
{
public:
	Axis();
	~Axis();
	void Update() override;
	void Draw() override;
};