#pragma once
#include "../Library/GameObject.h"
#include "Object3D.h"

/// <summary>
/// 3Dモデル ゲームオブジェクト
/// 
/// 3Dモデルを表示する
/// </summary>

class Model : public Object3D
{
public:
	Model();
	~Model();
	void Update() override;
};