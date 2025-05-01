#include "Model.h"

Model::Model()
{
	hModel = MV1LoadModel("data/Fighter.mv1"); // LoadGraph�Ƃ���Ȃ�

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
	//����ł��X�͉���Ă���
	//�ʓx�@�����W�A���ϊ��@�@�@(n�x * ���b��) / (��/180)
	//rotation.y += (180.0f * Time::DeltaTime() ) * DegToRad;	//1�b��180�x   "�~DegToRad"�F���W�A���ɂ���

	if (CheckHitKey(KEY_INPUT_D))
	{
		rotation.y += 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		rotation.y -= 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_W)) // �O�i
	{
		// Z�����ւ̃x�N�g���ɁA��]���̃x�N�g��
		VECTOR velocity = VGet(0, 0, 3) * MGetRotY(rotation.y);
		position += velocity;
	}
	
}
