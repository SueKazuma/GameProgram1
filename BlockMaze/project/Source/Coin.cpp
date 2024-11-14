#include "Coin.h"
#include "Player.h"
#include "Stage.h"

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
		position.y += v;//���V���^������������c
		v += 9.8f / 60; // �d��/60�t���[��

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
			v = -2.5;//���˂��(������Ȃ̂Łu-�v����)
		}
}

void Coin::Draw()
{
	Stage* s = FindGameObject<Stage>();
	DrawRectGraph(position.x - s->scroll, position.y, 40 * 3, 40 * 0, 40, 40, hImage, TRUE);
}


//�������i�񎟕������j�@
//[���w]�@y = ax ^ 2 + bx + c;	�@		���܂��A�g���܂���P�h�I
//[����]�@v = v0 + at�^v = v0 + gt�@	����:�� = v0:���� + gt:�����@��:����
//[�v���O����]�@x += v; v += g;