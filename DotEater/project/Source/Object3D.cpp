#include "Object3D.h"

Object3D::Object3D()
{
}

Object3D::~Object3D()
{
}

void Object3D::Update()
{
}

void Object3D::Draw()
{
	MATRIX mrx = MGetRotX(rotation.x); // X����]�s��
	MATRIX mry = MGetRotY(rotation.y); // Y����]�s��
	MATRIX mrz = MGetRotZ(rotation.z); // Z����]�s��
	MATRIX mt = MGetTranslate(position); // �ړ��s��
	MATRIX m = mrz * mrx * mry * mt;
	MV1SetMatrix(hModel, m);
	MV1DrawModel(hModel);
}
