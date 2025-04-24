#include "Model.h"

Model::Model()
{
	hModel = MV1LoadModel("data/Fighter.mv1"); // LoadGraph�Ƃ���Ȃ�

	rotation = VGet(0, 0, 0);
}

Model::~Model()
{
	MV1DeleteModel(hModel);
}

void Model::Update()
{
	//����ł��X�͉���Ă���

	//�ʓx�@�����W�A���ϊ��@�@�@�@�@n�x */���b�� / (180*��)
	rotation.z += (180.0f * Time::DeltaTime() ) * DegToRad;	//1�b��180�x

}

void Model::Draw()
{
	//DX_PI_F;�@�P�ς�=180�@
	MV1SetRotationXYZ(hModel, rotation);

	MV1SetPosition(hModel, VGet(0, 0, 0));  //�`��ʒu
	MV1DrawModel(hModel);					//DrawGraph�Ƃ���Ȃ�


}
