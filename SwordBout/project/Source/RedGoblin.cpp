#include "RedGoblin.h"
#include <assert.h>
#include "Stage.h"

#include "Player.h"

RedGoblin::RedGoblin() : RedGoblin(VGet(0,0,0), 0.0f){}

RedGoblin::RedGoblin(const VECTOR& pos, float rot)
{
	const std::string folder = "data/model/Character/RedGoblin/";
	hModel = MV1LoadModel((folder + "RedGoblin.mv1").c_str());
	assert(hModel > 0);

	animator = new Animator(hModel);
	assert(animator != nullptr);

	animator->AddFile(A_NEUTRAL,   folder + "Anim_Neutral.mv1",   true);
	animator->AddFile(A_WALK,      folder + "Anim_Walk.mv1",	true);
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

	state = ST_WAIT;
}

RedGoblin::~RedGoblin()
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

void RedGoblin::Update()
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

/// <summary>
/// ダメージを受ける。
/// </summary>
void RedGoblin::CheckAttack(VECTOR3 p1, VECTOR3 p2)
{
	MV1RefreshCollInfo(hModel);
	MV1_COLL_RESULT_POLY ret = MV1CollCheck_Line(hModel, -1, p1, p2);
	if (ret.HitFlag > 0)
	{
		animator->Play(A_DAMAGE);
		state = ST_DAMAGE;
	}
}

///////////////////
/// 各State関数 ///
///////////////////

void RedGoblin::UpdateWait()
{

}

void RedGoblin::UpdateDamage()
{
	if (animator->IsFinish())
	{
		animator->Play(A_NEUTRAL);
		state = ST_WAIT;
	}
}