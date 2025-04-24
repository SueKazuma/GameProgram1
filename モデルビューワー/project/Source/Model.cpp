#include "Model.h"

Model::Model()
{
	hModel = MV1LoadModel("data/Fighter.mv1"); // LoadGraphとおんなじ

	rotation = VGet(0, 0, 0);
}

Model::~Model()
{
	MV1DeleteModel(hModel);
}

void Model::Update()
{
	//それでも街は回っている

	//弧度法→ラジアン変換　　　　　n度 */何秒で / (180*π)
	rotation.z += (180.0f * Time::DeltaTime() ) * DegToRad;	//1秒で180度

}

void Model::Draw()
{
	//DX_PI_F;　１ぱい=180　
	MV1SetRotationXYZ(hModel, rotation);

	MV1SetPosition(hModel, VGet(0, 0, 0));  //描画位置
	MV1DrawModel(hModel);					//DrawGraphとおんなじ


}
