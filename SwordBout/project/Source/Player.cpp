#include "Player.h"
#include <assert.h>
#include "Stage.h"
#include "Camera.h"

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

	// �T�[�x�����f����ǂ�
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
	// �A�j���[�V�����̍X�V
	animator->Update();

	// �n�ɑ�������
#pragma region 
	Stage* stage = FindGameObject<Stage>();
	VECTOR pos1 = transform.position + VGet(0.0f, 100.0f, 0.0f);
	VECTOR pos2 = transform.position - VGet(0.0f, 100.0f, 0.0f);
	VECTOR hit; // �n�ʂ̍��W������ϐ�
	if (stage->CollideLine(pos1, pos2, &hit))
	{
		// �n�ʏ�����
		transform.position = hit;
	}
#pragma endregion

	// �J�������W���Z�b�g
	camera->SetPlayerPosition(transform.position);

	switch (state)
	{
	case Player::ST_NORMAL:
		UpdateNormal();
		break;
	case Player::ST_ATTACK1:
		UpdateAttack1();
		break;
	case Player::ST_ATTACK2:
		break;
	case Player::ST_ATTACK3:
		break;
	default:
		break;
	}
}

void Player::Draw()
{
	// �L�����̕`��
	Object3D::Draw();
	DrawLine3D(transform.position + moveVec * 100.0f, transform.position, GetColor(255.0f, 0.0f, 0.0f));

	// �T�[�x���̕`��
	MATRIX m = MV1GetFrameLocalWorldMatrix(hModel, 29);
	MV1SetMatrix(hSabel, m);
	MV1DrawModel(hSabel);

	VECTOR s1 = VGet(0.0f, 0.0f, 0.0f) * m;
	VECTOR s2 = VGet(0.0f, -100.0f, 0.0f) * m;
	DrawLine3D(s1, s2, GetColor(255.0f, 0.0f, 0.0f));
}

/// <summary>
/// State�֐��B
/// </summary>
void Player::UpdateNormal()
{
	// �ړ�
#pragma region
	// ���͂��x�N�g���ɒ���
	VECTOR3 inputVec = VECTOR3(0, 0, 0);
	if (CheckHitKey(KEY_INPUT_W))
	{
		inputVec += VECTOR3(0, 0, 1);
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		inputVec += VECTOR3(0, 0, -1);
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		inputVec += VECTOR3(1, 0, 0);
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		inputVec += VECTOR3(-1, 0, 0);
	}
	inputVec = inputVec.Normalize(); // ����1�̕�������

	if (inputVec.Size() > 0)
	{
		animator->Play(A_RUN);
		// �i�݂����x�N�g�������߂�(���ۂɐi�ރx�N�g��)
		//camera->GetTransform().rotation;�i�J�����̉�]���擾�j
		moveVec = inputVec * MGetRotY(camera->GetTransform().rotation.y);
		VECTOR3 front = VECTOR3(0, 0, 1) * MGetRotY(transform.rotation.y);
		VECTOR3 right = VECTOR3(1, 0, 0) * MGetRotY(transform.rotation.y);

		// ��]�����킹��(1F��60�x):�p�x������Ȃ���ΐi�܂Ȃ�
		// �R�T�C���I(����)
		float moveCos = VDot(moveVec, front);

		//float rightCos = VDot(moveVec, right);

		// cos��30�x�ȓ��Ȃ�i��
		if (moveCos >= cosf(30.0f * DegToRad)) // ���ʕt��
		{
			transform.position += moveVec * 5.0f;
			transform.rotation.y = atan2f(moveVec.x, moveVec.z);
		}
		// 30�x�ȏ�
		// �O
		else if (VDot(moveVec, right) >= 0.0f)
		{
			transform.rotation.y += 30.0f * DegToRad;
		}
		// ��
		else
		{
			transform.rotation.y -= 30.0f * DegToRad;
		}
	}
	else
	{
		animator->Play(A_NEUTRAL);
	}
#pragma endregion

	// �U��
#pragma region
	if (CheckHitKey(KEY_INPUT_M))
	{
		animator->Play(A_ATTACK1);
		state = State::ST_ATTACK1;
	}
#pragma endregion
}

void Player::UpdateAttack1()
{
	if (animator->IsFinish())
	{
		state = State::ST_NORMAL;
	}
}