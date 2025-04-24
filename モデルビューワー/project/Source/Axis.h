#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// 座標軸 ゲームオブジェクト
/// 
/// X,Y,Zの座標軸を表示する
/// </summary>

class Axis : public GameObject
{
public:
	Axis();
	~Axis();
	void Update() override;
	void Draw() override;
};