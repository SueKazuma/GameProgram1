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
	VECTOR pPos = p->GetPosition(); // �v���C���[�̑����̍��W

	pPos += VGet(0.0f, 50.0f, 0.0f); //�v���C���[���W�𓯂�������
	
	
	if (gotten)
	{
		//�s��-������Ƃ�
		VECTOR CtoP = (pPos - position);
		CtoP = VNorm(CtoP) * 5;
		position += CtoP;
		//player�ɂ����Â�
		float diff = VSize(pPos - position); // 2�_�Ԃ̋���
		if (diff < 10.0f) // �������Ă���
		{
			DestroyMe();
		}
	}
	else
	{
		float diff = VSize(pPos - position); // 2�_�Ԃ̋���
		if (diff < 120.0f) // �������Ă���
		{
			gotten = true;
		}
	}

	

	
}
