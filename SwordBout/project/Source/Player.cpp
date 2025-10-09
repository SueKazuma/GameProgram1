#include "Player.h"
#include <assert.h>
#include "Stage.h"
#include "Camera.h"
#include "PadInput.h"
#include "Goblin.h"

Player::Player() : Player(VGet(0,0,0), 0.0f){}

Player::Player(const VECTOR3& pos, float rot)
{
	const std::string folder = "data/model/Character/Player/";
	// �L�������f����ǂ�
	hModel = MV1LoadModel((folder + "PC.mv1").c_str());
	assert(hModel > 0);
	// ���[�g�m�[�h��Y����]����
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	animator = new Animator(hModel);
	assert(animator != nullptr);
	animator->AddFile(A_NEUTRAL,    folder + "Anim_Neutral.mv1",    true);
	animator->AddFile(A_RUN,        folder + "Anim_Run.mv1",        true);
	animator->AddFile(A_ATTACK1,    folder + "Anim_Attack1.mv1",    false);
	animator->AddFile(A_ATTACK2,    folder + "Anim_Attack2.mv1",    false);
	animator->AddFile(A_ATTACK3,    folder + "Anim_Attack3.mv1",    false);
	animator->AddFile(A_DAMAGE,     folder + "Anim_Damage.mv1",     false);
	animator->AddFile(A_BLOW_IN,    folder + "Anim_Blow_In.mv1",    false);
	animator->AddFile(A_BLOW_LOOP,  folder + "Anim_Blow_Loop.mv1",  true);
	animator->AddFile(A_BLOW_OUT,   folder + "Anim_Blow_Out.mv1",   false);
	animator->AddFile(A_DOWN,       folder + "Anim_Down_Loop.mv1",  true);
	animator->AddFile(A_GUARD_IN,   folder + "Anim_Guard_In.mv1",   false);
	animator->AddFile(A_GUARD_LOOP, folder + "Anim_Guard_Loop.mv1", true);
	animator->AddFile(A_GUARD_OUT,  folder + "Anim_Guard_Out.mv1",  false);
	animator->AddFile(A_JUMP_IN,    folder + "Anim_Jump_In.mv1",    false);
	animator->AddFile(A_JUMP_LOOP,  folder + "Anim_Jump_Loop.mv1",  true);
	animator->AddFile(A_JUMP_OUT,   folder + "Anim_Jump_Out.mv1",   false);
	animator->Play(A_NEUTRAL);

	transform.position = pos;
	transform.rotation.y = rot;

	camera = FindGameObject<Camera>();

	hSabel = MV1LoadModel("data/model/Character/Weapon/Sabel/Sabel.mv1");
	assert(hSabel > 0);
	
	state = ST_NORMAL;
}

Player::~Player()
{
	if (hModel > 0)
	{
		MV1DeleteModel(hModel);
		hModel = -1;
	}
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}
}
VECTOR3 moveVec;

void Player::Update()
{
	animator->Update();
	switch (state) {
	case ST_NORMAL:
		UpdateNormal();
		break;
	case ST_ATTACK1:
		UpdateAttack1();
		break;
	case ST_ATTACK2:
		UpdateAttack2();
		break;
	}

	Stage* stage = FindGameObject<Stage>();
	VECTOR hit; // �n�ʂ̍��W������ϐ�
	VECTOR pos1 = transform.position + VGet(0, 100, 0);
	VECTOR pos2 = transform.position + VGet(0, -100, 0);
	if (stage->CollideLine(pos1, pos2, &hit))
	{
		transform.position = hit;
	}
	camera->SetPlayerPosition(transform.position);
}

void Player::Draw()
{	
	Object3D::Draw(); // �L�����̕\��
	DrawLine3D(transform.position + moveVec*100, transform.position,
		GetColor(255,0,0));

	MATRIX m = MV1GetFrameLocalWorldMatrix(hModel, 29);
	MV1SetMatrix(hSabel, m);
	MV1DrawModel(hSabel);

	sabelBtm = VGet(0,0,0) * m;
	sabelTop = VGet(0,-100,0) * m;
	DrawLine3D(sabelBtm, sabelTop, GetColor(255,0,0));
}

void Player::UpdateNormal()
{
	// ���͂��x�N�g���ɒ���
	VECTOR3 inputVec = VECTOR3(0, 0, 0);
	PadInput* pad = FindGameObject<PadInput>();
	VECTOR2 inp = pad->LStickVec();
	inputVec.x = inp.x;
	inputVec.z = inp.y;
	// �i�݂����x�N�g�������߂�i���ۂɐi�ރx�N�g���j
	//�@�@�@�J�����̉�]�́Acamera->GetTransform().rotation�Ŏ�ɓ���
	if (inputVec.Size() > 0) {
		animator->Play(A_RUN);
		moveVec = inputVec * MGetRotY(camera->GetTransform().rotation.y);
		VECTOR3 front = VECTOR3(0, 0, 1) * MGetRotY(transform.rotation.y);
		VECTOR3 right = VECTOR3(1, 0, 0) * MGetRotY(transform.rotation.y);
		float moveCos = VDot(moveVec, front);
		if (moveCos >= cosf(30.0f * DegToRad)) { // ���ʕt��
			transform.position += moveVec * 5.0f;
			transform.rotation.y = atan2f(moveVec.x, moveVec.z);
		} else if (VDot(moveVec, right) >= 0) {
			transform.rotation.y += 30.0f * DegToRad;
		} else {
			transform.rotation.y -= 30.0f * DegToRad;
		}
	} else {
		animator->Play(A_NEUTRAL);
	}
	if (pad->OnPush(XINPUT_BUTTON_A)) // �U��
	{
		animator->Play(A_ATTACK1);
		attackNext = false;
		state = ST_ATTACK1; //��Ԃ�ς���
	}
}

void Player::UpdateAttack1()
{
	if (animator->GetCurrentFrame() >= 8.5f) {
		if (attackNext) {
			animator->Play(A_ATTACK2);
			attackNext = false;
			state = ST_ATTACK2;
		}
	} else {
		Goblin* gob = FindGameObject<Goblin>();
		gob->CheckAttack(sabelBtm, sabelTop);

		PadInput* pad = FindGameObject<PadInput>();
		if (pad->OnPush(XINPUT_BUTTON_A))
		{
			attackNext = true;
		}
	}
	if (animator->IsFinish()) { // �U���A�j���[�V�������I�����
		state = ST_NORMAL; //��Ԃ�ς���
	}
}

void Player::UpdateAttack2()
{
	if (animator->IsFinish()) { // �U���A�j���[�V�������I�����
		state = ST_NORMAL; //��Ԃ�ς���
	}
}
