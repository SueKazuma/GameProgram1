#include "Coin.h"
#include "Player.h"

Coin::Coin()
{
	//�R���X�g���N�^�ŊG�����[�h
	hImage = LoadGraph("data/image/parts.png");
	got = false;
}

Coin::~Coin()
{
	DeleteGraph(hImage);
}

void Coin::Update()
{
	if (got) //���ꂽ��
	{
		position.y -= 3;//���V���^������������c
		counter -= 1;
		if (counter == 0)
		{
			DestroyMe();//���ʂ����Ȃ�����Ȃ��I
		}
		return;//�I���I��I�ȏ�I�F���U�I
	}
	
	//�����O
		//�����蔻��
		Player* p = FindGameObject<Player>();//�C���X�^���X�FPlayer��T��
		VECTOR2 playerPos = p->position;//playerPos��player��position������
		//�����蔻��F"playerPos"��"position"������������
		if (CircleHit(position, playerPos, 40))
		{
			got = true;//���ꂽ�I
			counter = 20;//���ւ̃J�E���^�[�Q�O�t���[��
		}
}

void Coin::Draw()
{
	DrawRectGraph(position.x, position.y,   40 * 3, 40 * 0,   40, 40, hImage, TRUE);
}
