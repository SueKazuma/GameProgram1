#include "Model.h"

Model::Model()
{
	hModel = MV1LoadModel("data/Fighter.mv1"); // LoadGraphとおんなじ

	rotation = VGet(0, 0, 0);
	position = VGet( 0, 0, 0);

	//rotation.x = 30.0f * DegToRad;
	//rotation.z = 30.0f * DegToRad;
}

Model::~Model()
{
	MV1DeleteModel(hModel);
}

void Model::Update()
{
	//それでも街は回っている
	//弧度法→ラジアン変換　　　(n度 * 何秒で) / (π/180)
	//rotation.y += (180.0f * Time::DeltaTime() ) * DegToRad;	//1秒で180度   "×DegToRad"：ラジアンにする

	if (CheckHitKey(KEY_INPUT_D))
	{
		rotation.y += 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		rotation.y -= 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_W)) // 前進
	{
		// Z方向へのベクトルに、回転軸のベクトル
		VECTOR velocity = VGet(0, 0, 3) * MGetRotY(rotation.y);
		position += velocity;
	}
	
}
