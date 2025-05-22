#include "Coin.h"
#include "Player.h"

Coin::Coin(VECTOR pos)
{
	hModel = MV1LoadModel("data/models/Coin.mv1");
	position = pos;
	gotten = false;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	Player* pl = FindGameObject<Player>();
	VECTOR pPos = pl->GetPosition(); // �v���C���[�̑����̍��W
	pPos += VGet(0,50,0); // �R�C���Ɠ��������ɂ���

	if (gotten) {
		homingUpdate();
#if false
		// ���ꂽ�̂ŁA�v���C���[�ɋ߂Â�
		// �P�D�R�C������v���C���[�Ɍ������x�N�g�������
		VECTOR v = pPos - position;
		// �Q�D���̃x�N�g���̒�����5�̂��̂����i�R�C���̈ړ��x�N�g���j
		v = VNorm(v) * 5.0f; // VNorm()�̓x�N�g���̒������P�ɂ���֐�
		// �R�D�R�C���̍��W�ɉ�����
		position += v;
		// �S�D�R�C���ƃv���C���[�̋�����10�ȉ��ɂȂ�����DestroyMe()
		float diff = VSize(pPos - position);
		if (diff < 10.0f) {
			DestroyMe();
		}
#endif
	} else {
		float diff = VSize(pPos - position);
		if (diff < 120.0f) { // �R�C���ɓ������Ă�
			gotten = true;
			homingStart();
		}
	}
}

void Coin::homingStart()
{
	Player* pl = FindGameObject<Player>();
	VECTOR pPos = pl->GetPosition(); // �v���C���[�̑����̍��W
	pPos += VGet(0, 50, 0); // �R�C���Ɠ��������ɂ���
	VECTOR v = pPos - position;
	velocity = VNorm(v) * -20.0f; // �����~�ړ����x
}

void Coin::homingUpdate()
{
	position += velocity;

	Player* pl = FindGameObject<Player>();
	VECTOR pPos = pl->GetPosition(); // �v���C���[�̑����̍��W
	pPos += VGet(0, 50, 0); // �R�C���Ɠ��������ɂ���
	VECTOR v = pPos - position; // ����ւ̃x�N�g��
	if (VSize(v) < 20.0f) {
		DestroyMe();
	}

	VECTOR a = VNorm(velocity); // �����̐���
	VECTOR b = VNorm(v); // ����ւ̃x�N�g���̌���
	float co = VDot(a, b); // ���ꂪcos��
	float speed = (co+1.0f)* 10.0f; // �Ƃ�0���Ƒ����A�Ƃ��傫���ƒx��
						// co�̓Ƃ�1�`-1�ɂȂ�̂ŁA1�̂Ƃ���20�A-1�̎���0
	float len = VSize(velocity); // ���̒���
	if (len > speed) { // ������
		len -= 0.1f;
	} else { // �x����
		len += 0.05f;
	}
	velocity = VNorm(velocity) * len;

	VECTOR rightVec = velocity * MGetRotY(90.0f * DegToRad); // �E�x�N�g��
	float ip = VDot(rightVec, v); // ���ς����߂�
	// ������Ίp�x���������A�x����Ίp�x��傫��
	float rspeed = (25.0f-len)/ 5.0f;
	if (ip > 0) { // �E�ɂ���
		velocity = velocity * MGetRotY(rspeed * DegToRad); // �E����
	} else {
		velocity = velocity * MGetRotY(-rspeed * DegToRad); // ������
	}
}











