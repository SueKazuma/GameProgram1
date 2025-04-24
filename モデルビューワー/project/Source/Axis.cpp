#include "Axis.h"

Axis::Axis()
{
}

Axis::~Axis()
{
}

void Axis::Update()
{
}

void Axis::Draw()
{
	SetCameraPositionAndTarget_UpVecY(VGet(100, 200, -300), VGet(0, 0, 0));//(俯瞰、俯瞰、手前)
	//SetCameraPositionAndTarget_UpVecY(VGet(0, 300, -10), VGet(0, 0, 0));//y軸視点
	//SetCameraPositionAndTarget_UpVecY(VGet(-10, 0, 300), VGet(0, 0, 0));//z軸視点


	DrawLine3D(VGet(-100, 0, 0), VGet(100, 0, 0), GetColor(255, 0, 0));
	DrawCone3D(VGet(100, 0, 0), VGet(60, 0, 0), 5, 20, GetColor(255, 0, 0), GetColor(255, 0, 0), 1);
	
	DrawLine3D(VGet(0, -100, 0), VGet(0, 100, 0), GetColor(0, 255, 0));
	DrawCone3D(VGet(0, 100, 0), VGet(0, 60, 0), 5, 20, GetColor(0, 255, 0), GetColor(0, 255, 0), 1);
	
	DrawLine3D(VGet(0, 0, -100), VGet(0, 0, 100), GetColor(0, 0, 255));
	DrawCone3D(VGet(0, 0, 100), VGet(0, 0, 60), 5, 20, GetColor(0, 0, 255), GetColor(0, 0, 255), 1);

	//3つ
	//VECTOR Red 
}
