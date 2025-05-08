#include "Player.h"

Player::Player()
{
	hModel = MV1LoadModel("data/models/WhiteChara.mv1");
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);

	
}

Player::Player(VECTOR pos)
{
	hModel = MV1LoadModel("data/models/WhiteChara.mv1");
	rotation = VGet(0, 0, 0);
	position = pos;
	//Y���ŃΉ񂵂Ă�
	MV1SetFrameUserLocalMatrix(hModel, 6, MGetRotY(DX_PI_F));

	anim = new Animator(hModel); // ���̉�
	//anim->LoadFile("data/models/Anim_Idle.mv1");
	anim->AddFile(0, "data/models/Anim_Idle.mv1",true);//0��Idle�A���[�v�I
	anim->AddFile(1, "data/models/Anim_Run.mv1", true);//1��Run�A���[�v�I
	anim->Play(0);
}

Player::~Player()
{
}

void Player::Update()
{
	anim->Update();
	if (CheckHitKey(KEY_INPUT_W))
	{
		anim->Play(1);
	}
	else
	{
		anim->Play(0);
	}
}