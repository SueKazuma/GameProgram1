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
	Player* p = FindGameObject<Player>();
	VECTOR pPos = p->GetPosition();  // �v���C���[�̑����̍��W
	pPos += VGet(0.0f, 50.0f, 0.0f); //�v���C���[���W�𓯂�������
	
	
	if (gotten)
	{
		homingUpdate();
#if false
		// �s�� - ���ݒn
		//�P�D�R�C�����v���C���[�̃x�N�g��
		VECTOR CtoP = (pPos - position);
		//�Q�D�x�N�g���̒������T�̂��̂����
		CtoP = VNorm(CtoP) * 5;
		//�R�D�R�C���̍��W�ɉ�����
		position += CtoP;
		//�S�D�R�C���ƃv���C���[�̋������P�O�ȉ��ɂȂ�����
		float diff = VSize(pPos - position); // 2�_�Ԃ̋���
		if (diff < 10.0f) // �������Ă���
		{
			DestroyMe();
		}
#endif
	}
	else
	{
		float diff = VSize(pPos - position); // 2�_�Ԃ̋���
		if (diff < 120.0f) // �R�C���ɓ������Ă���
		{
			gotten = true;
			homingStart();
		}
	}
	
}

void Coin::homingStart() // ���ɔ�΂�
{
	Player* p = FindGameObject<Player>();
	VECTOR pPos = p->GetPosition();  // �v���C���[�̑����̍��W
	pPos += VGet(0.0f, 50.0f, 0.0f); //�v���C���[���W�𓯂�������
	VECTOR v = pPos - position;
	velocity = VNorm(v) * -10.0f; // �����~�ړ����x �܂�"Normalize"�͌����������o��
}

void Coin::homingUpdate() // ����
{
	position += velocity;

	Player* p = FindGameObject<Player>();
	VECTOR pPos = p->GetPosition();  // �v���C���[�̑����̍��W
	pPos += VGet(0.0f, 50.0f, 0.0f); //�v���C���[���W�𓯂�������

	VECTOR v = pPos - position; // ����ւ̃x�N�g��
	if (VSize(v) < 20.0f) 
	{
		DestroyMe();
	}

	VECTOR a = VNorm(velocity); // �����̐���
	VECTOR b = VNorm(v);        // ����ւ̃x�N�g���̌���
	float co = VDot(a, b);
	float speed = (co + 1.0f) * 10.0f; // ����0�x�Ȃ瑬���A����90�x�Ȃ�x��
	// co�̓����P�`-�P�ɂȂ�̂ŁA�P�̂Ƃ��Q�O�A-�P�̂Ƃ��O

	float len = VSize(velocity);	  // ���̒���
	if (len > speed) // ���X�M�B�I
	{
		len -= 0.05f;
	}
	else			 // �x�X�M�B�I
	{
		len += 0.05f;
	}
	velocity = VNorm(velocity) * len;

	VECTOR rightVec = velocity * MGetRotY(90.0f * DegToRad);
	float ip = VDot(rightVec, v); // ���ς����߂�
	// ������Ίp�x���������A�x����Α傫��
	float rspeed = (25.0f - len) / 5.0f;
	if (ip > 0) // �E�ɂ���
	{
		velocity = velocity * MGetRotY( rspeed * DegToRad);  // �E����
	}
	else
	{
		velocity = velocity * MGetRotY(-rspeed * DegToRad); // ������
	}
}
