#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// 3Dモデル ゲームオブジェクト
/// 
/// 3Dモデルを表示する
/// </summary>

class Model : public GameObject
{
public:
	Model();
	~Model();
	void Update() override;
	void Draw() override;
	//int GethModel() { return hModel; }　やるならコレ

private: // 変数は基本すべてプライベート！！！！！！！！！！！！！！！！！！
	int hModel;
	VECTOR rotation;
};