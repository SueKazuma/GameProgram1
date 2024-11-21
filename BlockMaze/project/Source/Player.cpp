#include "Player.h"
#include "Stage.h"
#include "config.h"
#include "GoalText.h"

//�uconst�v�F�萔�͏����������Ȃ��I
const float Gravity = 0.3f;
const float JumpHight = 40 * 2;						 //�W�����v�̍���
//			v0 = -  ��   2   *   g     *    S
const float V0 = -sqrtf(2.0f * Gravity * JumpHight); //������(�W�����v)�̎�

Player::Player()
{
	hImage = LoadGraph("data/image/chara.png");
	position.x = 0;
	position.y = 0;

	speed = 3.0f;

	goaled = false;
}

Player::~Player()
{
	DeleteGraph(hImage);
}

void Player::Update()
{
	Stage* s = FindGameObject<Stage>();

	//�ȒP������ ���Ԓ�~���mAV�ɂȂ�
	//if (goaled)
	//{
	//   return;
	//}

	if (!goaled)
	{
		/*
	if (CheckHitKey(KEY_INPUT_W))
	{
		position.y -= speed;//��
		//��ɕǂ����邩���ׂ�
		int push = s->IsWallUp(position + VECTOR2(0, 0));
		position.y += push;
		push = s->IsWallUp(position + VECTOR2(39, 0));
		position.y += push;
	}*/
		/*
	if (CheckHitKey(KEY_INPUT_S))
	{
		position.y += speed;//��
		//���ɕǂ����邩���ׂ�
		int push = s->IsWallDown(position + VECTOR2(0, 39));
		position.y -= push;
		push = s->IsWallDown(position + VECTOR2(39, 39));
		position.y -= push;
	}*/
		if (CheckHitKey(KEY_INPUT_A))
		{
			position.x -= speed;//��
			//���ɕǂ����邩���ׂ�
			int push = s->IsWallLeft(position + VECTOR2(0, 0));
			position.x += push;
			push = s->IsWallLeft(position + VECTOR2(0, 39));
			position.x += push;
		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			position.x += speed;//�E
			//�E�ɕǂ����邩���ׂ�
			int push = s->IsWallRight(position + VECTOR2(39, 0));
			position.x -= push;
			push = s->IsWallRight(position + VECTOR2(39, 39));
			position.x -= push;
		}

		//�W�����v
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			if (prevJumpKey == false)
			{
				if (onGround == true)
				{
					//2�}�X����� velocity:���x
					velocity = V0;//�W�����v�@������̗� "���������߂�"
				}
			}
			prevJumpKey = true;
		}
		else
		{
			prevJumpKey = false;
		}
	}
	

	//�d��
	position.y += velocity;//���W�ɂ͑��x�𑫂�
	velocity += Gravity;//�������̗́@���x�ɂ͏d�͂𑫂�
	onGround = false;


	//���ɕǂ����邩���ׂ�
	if (velocity >= 0)// velocity:���x
	{
		int push = s->IsWallDown(position + VECTOR2(0, 40)); //���������̂�40
		if (push > 0)	//�n�ʂɐG�ꂽ�̂�
		{
			velocity = 0;			//�n�ʂɐG�����瑬�x��0��
			position.y -= push - 1; //�n�ʂ̏�ɉ����Ԃ�	1��������̂�push-1
			onGround = true;		//�ڒn���Ă�
		}
		push = s->IsWallDown(position + VECTOR2(39, 40));	 //�����������������̂�40
		if (push > 0)	//�n�ʂɐG�ꂽ�̂�
		{
			velocity = 0;			//�n�ʂɐG�����瑬�x��0��
			position.y -= push - 1; //�n�ʂ̏�ɉ����Ԃ�	1��������̂�push-1
			onGround = true;		//�ڒn���Ă�
		}
	}
	//��ɕǂ����邩���ׂ�
	else
	{
		int push = s->IsWallUp(position + VECTOR2(0, 0));
		if (push > 0) 
		{
			velocity = 0.0f;
			position.y += push;
			
			
		}
		push = s->IsWallUp(position + VECTOR2(39, 0));
		if (push > 0)
		{
			velocity = 0.0f;
			position.y += push;
		}
	}
	

	//�v���C���[�ɍ��킹�ăX�N���[��(�i�s)
	if (position.x - s->scroll > 400) //�v���C���[�̍��W��400�ȏ�
	{
		s->scroll = position.x - 400; //�X�N���[�����x���v���C���[�ɍ��킹��
	}
	//�v���C���[�ɍ��킹�ăX�N���[��(���)
	if (position.x - s->scroll < 300) //�v���C���[�̍��W��300�ȉ�
	{
		s->scroll = position.x - 300; //�X�N���[�����x���v���C���[�ɍ��킹��
	}

	if (s->IsGoal(position + VECTOR2(20, 20))) //�S�[���͍���łȂ����S�Łi�E��20,����20�����j
	{
		goaled = true;
		Instantiate<GoalText>();
	}
}

void Player::Draw()
{
	Stage* s = FindGameObject<Stage>();
	DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 40, 40, hImage, TRUE);
}