#include "Player.h"
#include <assert.h>
#include "Stage.h"
#include "Camera.h"

Player::Player() : Player(VGet(0,0,0), 0.0f){}

Player::Player(const VECTOR3& pos, float rot)
{
	const std::string folder = "data/model/Character/Player/";
	// キャラモデルを読む
	hModel = MV1LoadModel((folder + "PC.mv1").c_str());
	assert(hModel > 0);
	// ルートノードをY軸回転する
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

	// サーベルモデルを読む
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
	// アニメーションの更新
	animator->Update();

	// 地に足着ける
#pragma region 
	Stage* stage = FindGameObject<Stage>();
	VECTOR pos1 = transform.position + VGet(0.0f, 100.0f, 0.0f);
	VECTOR pos2 = transform.position - VGet(0.0f, 100.0f, 0.0f);
	VECTOR hit; // 地面の座標が入る変数
	if (stage->CollideLine(pos1, pos2, &hit))
	{
		// 地面上を歩く
		transform.position = hit;
	}
#pragma endregion

	// カメラ座標をセット
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
	// キャラの描画
	Object3D::Draw();
	DrawLine3D(transform.position + moveVec * 100.0f, transform.position, GetColor(255.0f, 0.0f, 0.0f));

	// サーベルの描画
	MATRIX m = MV1GetFrameLocalWorldMatrix(hModel, 29);
	MV1SetMatrix(hSabel, m);
	MV1DrawModel(hSabel);

	VECTOR s1 = VGet(0.0f, 0.0f, 0.0f) * m;
	VECTOR s2 = VGet(0.0f, -100.0f, 0.0f) * m;
	DrawLine3D(s1, s2, GetColor(255.0f, 0.0f, 0.0f));
}

/// <summary>
/// State関数。
/// </summary>
void Player::UpdateNormal()
{
	// 移動
#pragma region
	// 入力をベクトルに直す
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
	inputVec = inputVec.Normalize(); // 長さ1の方向だけ

	if (inputVec.Size() > 0)
	{
		animator->Play(A_RUN);
		// 進みたいベクトルを求める(実際に進むベクトル)
		//camera->GetTransform().rotation;（カメラの回転を取得）
		moveVec = inputVec * MGetRotY(camera->GetTransform().rotation.y);
		VECTOR3 front = VECTOR3(0, 0, 1) * MGetRotY(transform.rotation.y);
		VECTOR3 right = VECTOR3(1, 0, 0) * MGetRotY(transform.rotation.y);

		// 回転を合わせる(1Fで60度):角度が合わなければ進まない
		// コサイン！(内積)
		float moveCos = VDot(moveVec, front);

		//float rightCos = VDot(moveVec, right);

		// cosが30度以内なら進む
		if (moveCos >= cosf(30.0f * DegToRad)) // 正面付近
		{
			transform.position += moveVec * 5.0f;
			transform.rotation.y = atan2f(moveVec.x, moveVec.z);
		}
		// 30度以上
		// 前
		else if (VDot(moveVec, right) >= 0.0f)
		{
			transform.rotation.y += 30.0f * DegToRad;
		}
		// 後
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

	// 攻撃
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