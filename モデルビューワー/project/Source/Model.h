#pragma once
#include "../Library/GameObject.h"
#include "Object3D.h"

/// <summary>
/// 3D���f�� �Q�[���I�u�W�F�N�g
/// 
/// 3D���f����\������
/// </summary>

class Model : public Object3D
{
public:
	Model();
	~Model();
	void Update() override;
};