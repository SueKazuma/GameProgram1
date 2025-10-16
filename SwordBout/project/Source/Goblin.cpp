#include "Goblin.h"
#include <assert.h>
#include "Stage.h"

#include "Player.h"

Goblin::Goblin() : Goblin(VGet(0,0,0), 0.0f) {}

Goblin::Goblin(const VECTOR& pos, float rot)
{
	const std::string folder = "data/model/Character/Goblin/";
	hModel = MV1LoadModel((folder + "Goblin.mv1").c_str());
	assert(hModel > 0);
	MV1SetupCollInfo(hModel);

	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	animator = new Animator(hModel);
	assert(animator != nullptr);

	animator->AddFile(A_NEUTRAL,   folder + "Anim_Neutral.mv1",   true);
	animator->AddFile(A_WALK,      folder + "Anim_Walk.mv1",      true);
	animator->AddFile(A_RUN,       folder + "Anim_Run.mv1",       true);
	animator->AddFile(A_ATTACK1,   folder + "Anim_Attack1.mv1",   false);
	animator->AddFile(A_DAMAGE,    folder + "Anim_Damage.mv1",    false);
	animator->AddFile(A_BLOW_IN,   folder + "Anim_Blow_In.mv1",   false);
	animator->AddFile(A_BLOW_LOOP, folder + "Anim_Blow_Loop.mv1", true);
	animator->AddFile(A_BLOW_OUT,  folder + "Anim_Blow_Out.mv1",  false);
	animator->AddFile(A_DOWN,      folder + "Anim_Down_Loop.mv1",      true);
	animator->Play(A_NEUTRAL);

	transform.position = pos;
	transform.rotation.y = rot;

	territory.center = pos;
	territory.range = 2000.0;

	state = ST_WAIT;
}

Goblin::~Goblin()
{
	if (animator != nullptr) 
	{
		delete animator;
		animator = nullptr;
	}

	if (hModel > 0) 
	{
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Goblin::Update()
{
	animator->Update();

	// 状態遷移
	switch (state)
	{
	case ST_WAIT:
		UpdateWait();
		break;
	case ST_DAMAGE:
		UpdateDamage();
		break;
	case ST_CHASE:
		UpdateChase();
		break;
	case ST_ATTACK:
		UpdateAttack();
		break;
	case ST_BACK:
		UpdateBack();
		break;
	}

	// 地を歩く
	Stage* stage = FindGameObject<Stage>();
	VECTOR hit; // 地面の座標が入る変数
	VECTOR pos1 = transform.position + VGet(0, 100, 0);
	VECTOR pos2 = transform.position + VGet(0, -100, 0);
	if (stage->CollideLine(pos1, pos2, &hit))
	{
		transform.position = hit;
	}
}

///////////////////
/// 各State関数 ///
///////////////////

void Goblin::CheckAttack(VECTOR3 p1, VECTOR3 p2)
{
	MV1RefreshCollInfo(hModel);
	MV1_COLL_RESULT_POLY ret = MV1CollCheck_Line(hModel, -1, p1, p2);
	if (ret.HitFlag > 0) 
	{
		animator->Play(A_DAMAGE);
		state = ST_DAMAGE;
	}
}

void Goblin::UpdateWait()
{
	Player* player = FindGameObject<Player>();
	VECTOR3 playerPos = player->GetTransform().position;
	VECTOR3 toPlayer = playerPos - transform.position;

	VECTOR3 front = VECTOR3(0, 0, 1) * MGetRotY(transform.rotation.y);
	float cosT = VDot(toPlayer.Normalize(), front); // 内積

	if (toPlayer.Size() > 1000.0f)
		return;

	if (cosT >= cos(60*DegToRad) ) // コンタクト！
	{
		animator->Play(A_RUN);
		state = ST_CHASE;
	}
}



void Goblin::UpdateChase()
{
	Player* player = FindGameObject<Player>();
	VECTOR3 playerPos = player->GetTransform().position;

	float d = MoveTo(territory.center, 6, 6);
	// 近づいたら
	if (d < 100.0f)
	{
		animator->Play(A_ATTACK1);
		state = ST_ATTACK;
	}

	// テリトリーでたらback
	VECTOR3 toTerritory = territory.center - transform.position;
	if ( toTerritory.Size() >= territory.range) 
	{
		animator->Play(A_WALK);
		state = ST_BACK;
	}
}

void Goblin::UpdateAttack()
{
	if (animator->IsFinish())
	{
		animator->Play(A_NEUTRAL);
		state = ST_WAIT;
	}
}

void Goblin::UpdateBack()
{
	// 見えてたら追いかける
	// 見えてなかったら帰る

	float d = MoveTo(territory.center, 3, 6);
	if (d < 100.0f)
	{
		animator->Play(A_NEUTRAL);
		state = ST_WAIT;
	}
}

void Goblin::UpdateDamage()
{
	if (animator->IsFinish())
	{
		animator->Play(A_NEUTRAL);
		state = ST_WAIT;
	}
}

/// <summary>
/// 設定地点に向かう！共通！！！
/// </summary>
/// <param name="toPosition"></param>
/// <param name="moveSpeed"></param>
/// <param name="rotateSpeed"></param>
void Goblin::GoTo(VECTOR3 toPosition, float moveSpeed, float rotateSpeed)
{
	// 前進
	VECTOR3 velocity = VECTOR3(0, 0, moveSpeed) * MGetRotY(transform.rotation.y);
	transform.position += velocity;
	// 回転
	VECTOR3 right = VECTOR3(rotateSpeed, 0, 0) * MGetRotY(transform.rotation.y);

	float ip = VDot(right, toPosition);
	if (ip >= 0)  // migi
	{
		transform.rotation.y += DegToRad;
	}
	else
	{
		transform.rotation.y -= DegToRad;
	}
}

/// <summary>
/// 正しい共通
/// </summary>
/// <param name="targetPosition"></param>
/// <param name="moveSpeed"></param>
/// <param name="rotateSpeed"></param>
/// <returns></returns>
float Goblin::MoveTo(VECTOR3 targetPosition, float moveSpeed, float rotateSpeed)
{
	VECTOR3 toTarget = territory.center - transform.position;

	// 前進
	VECTOR3 velocity = VECTOR3(0, 0, moveSpeed) * MGetRotY(transform.rotation.y);
	transform.position += velocity;
	// 回転
	VECTOR3 right = VECTOR3(rotateSpeed, 0, 0) * MGetRotY(transform.rotation.y);

	float ip = VDot(right, toTarget);
	if (ip >= 0)  // migi
	{
		transform.rotation.y += DegToRad;
	}
	else
	{
		transform.rotation.y -= DegToRad;
	}
	return toTarget.Size();
}
