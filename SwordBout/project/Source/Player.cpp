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
	// ƒLƒƒƒ‰ƒ‚ƒfƒ‹‚ğ“Ç‚Ş
	hModel = MV1LoadModel((folder + "PC.mv1").c_str());
	assert(hModel > 0);
	// ƒ‹[ƒgƒm[ƒh‚ğY²‰ñ“]‚·‚é
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
<<<<<<< HEAD
	
=======

>>>>>>> ä¸Šæ›¸ãå‰ï¼Ÿ
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
	switch (state) 
	{
	case ST_NORMAL:
		UpdateNormal();
		break;
	case ST_ATTACK1:
		UpdateAttack1();
		break;
<<<<<<< HEAD
=======
	case Player::ST_ATTACK2:
		UpdateAttack2();
		break;
	case Player::ST_ATTACK3:
		UpdateAttack3();
		break;
	default:
		break;
>>>>>>> ä¸Šæ›¸ãå‰ï¼Ÿ
	}

	Stage* stage = FindGameObject<Stage>();
	VECTOR hit; // ’n–Ê‚ÌÀ•W‚ª“ü‚é•Ï”
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
	Object3D::Draw(); // ƒLƒƒƒ‰‚Ì•\¦
	DrawLine3D(transform.position + moveVec*100, transform.position,
		GetColor(255,0,0));

<<<<<<< HEAD
	MATRIX m = MV1GetFrameLocalWorldMatrix(hModel, 29);
	MV1SetMatrix(hSabel, m);
	MV1DrawModel(hSabel);

	VECTOR s1 = VGet(0,0,0) * m;
	VECTOR s2 = VGet(0,-100,0) * m;
	DrawLine3D(s1, s2, GetColor(255,0,0));
=======
	// ƒT[ƒxƒ‹‚Ì•`‰æ
	m = MV1GetFrameLocalWorldMatrix(hModel, 29);
	sabelBtm = VGet(0.0f, 0.0f, 0.0f) * m;
	sabelTop = VGet(0.0f, -100.0f, 0.0f) * m;

	MV1SetMatrix(hSabel, m);
	MV1DrawModel(hSabel);
	// ƒT[ƒxƒ‹ƒ‰ƒCƒ“
	DrawLine3D(sabelBtm, sabelTop, GetColor(255.0f, 0.0f, 0.0f));
>>>>>>> ä¸Šæ›¸ãå‰ï¼Ÿ
}

void Player::UpdateNormal()
{
	// “ü—Í‚ğƒxƒNƒgƒ‹‚É’¼‚·
	VECTOR3 inputVec = VECTOR3(0, 0, 0);
	PadInput* pad = FindGameObject<PadInput>();
	VECTOR2 inp = pad->LStickVec();
	inputVec.x = inp.x;
	inputVec.z = inp.y;
	// i‚İ‚½‚¢ƒxƒNƒgƒ‹‚ğ‹‚ß‚éiÀÛ‚Éi‚ŞƒxƒNƒgƒ‹j
	// ƒJƒƒ‰‚Ì‰ñ“]‚ÍAcamera->GetTransform().rotation‚Åè‚É“ü‚é
	if (inputVec.Size() > 0) {
		animator->Play(A_RUN);
		moveVec = inputVec * MGetRotY(camera->GetTransform().rotation.y);
		VECTOR3 front = VECTOR3(0, 0, 1) * MGetRotY(transform.rotation.y);
		VECTOR3 right = VECTOR3(1, 0, 0) * MGetRotY(transform.rotation.y);
		float moveCos = VDot(moveVec, front);
		if (moveCos >= cosf(30.0f * DegToRad)) { // ³–Ê•t‹ß
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
<<<<<<< HEAD
	if (pad->OnPush(XINPUT_BUTTON_A)) // UŒ‚
=======
#pragma endregion

	// UŒ‚
#pragma region
	if (pad->OnPush(XINPUT_BUTTON_A) )
>>>>>>> ä¸Šæ›¸ãå‰ï¼Ÿ
	{
		canNextAttack = false;
		animator->Play(A_ATTACK1);
		state = ST_ATTACK1; //ó‘Ô‚ğ•Ï‚¦‚é
	}
}

void Player::UpdateAttack1()
{
<<<<<<< HEAD
	if (animator->IsFinish()) { // UŒ‚ƒAƒjƒ[ƒVƒ‡ƒ“‚ªI‚í‚Á‚½
		state = ST_NORMAL; //ó‘Ô‚ğ•Ï‚¦‚é
=======
	// UŒ‚“ü—Í•ªŠò
	if (animator->GetCurrentFrame() >= 8.5f)
	{
		if (canNextAttack)
		{
			canNextAttack = false;
			animator->Play(A_ATTACK2);
			state = State::ST_ATTACK2;
		}
		else if (animator->IsFinish())
		{
			canNextAttack = false;
			state = State::ST_NORMAL;
		}
	}
	else 
	{
		PadInput* pad = FindGameObject<PadInput>();
		if (pad->OnPush(XINPUT_BUTTON_A)) 
		{
			canNextAttack = true;
		}

		Goblin* goblin = FindGameObject<Goblin>();
		goblin->CheckAttack(sabelBtm, sabelTop);
	}
}

void Player::UpdateAttack2()
{
	// UŒ‚“ü—Í•ªŠò
	if (animator->GetCurrentFrame() >= 8.5f)
	{
		if (canNextAttack)
		{
			canNextAttack = false;
			animator->Play(A_ATTACK3);
			state = State::ST_ATTACK3;
		}
		else if (animator->IsFinish())
		{
			canNextAttack = false;
			state = State::ST_NORMAL;
		}
	}
	else
	{
		PadInput* pad = FindGameObject<PadInput>();
		if (pad->OnPush(XINPUT_BUTTON_A))
		{
			canNextAttack = true;
		}
	}
}

void Player::UpdateAttack3()
{
	// UŒ‚I—¹ŒãAƒAƒCƒhƒ‹ó‘Ô‚Ö
	if (animator->IsFinish())
	{
		state = State::ST_NORMAL;
>>>>>>> ä¸Šæ›¸ãå‰ï¼Ÿ
	}
}
