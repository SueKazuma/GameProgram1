#include "Player.h"
#include "Stage.h"
#include "config.h"
#include "GoalText.h"

//「const」：定数は書き換えられない！
const float Gravity = 0.3f;
const float JumpHight = 40 * 2;						 //ジャンプの高さ
//			v0 = -  √   2   *   g     *    S
const float V0 = -sqrtf(2.0f * Gravity * JumpHight); //放物線(ジャンプ)の式

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

	//簡単だけど 時間停止モノAVになる
	//if (goaled)
	//{
	//   return;
	//}

	if (!goaled)
	{
		/*
	if (CheckHitKey(KEY_INPUT_W))
	{
		position.y -= speed;//上
		//上に壁があるか調べる
		int push = s->IsWallUp(position + VECTOR2(0, 0));
		position.y += push;
		push = s->IsWallUp(position + VECTOR2(39, 0));
		position.y += push;
	}*/
		/*
	if (CheckHitKey(KEY_INPUT_S))
	{
		position.y += speed;//下
		//下に壁があるか調べる
		int push = s->IsWallDown(position + VECTOR2(0, 39));
		position.y -= push;
		push = s->IsWallDown(position + VECTOR2(39, 39));
		position.y -= push;
	}*/
		if (CheckHitKey(KEY_INPUT_A))
		{
			position.x -= speed;//左
			//左に壁があるか調べる
			int push = s->IsWallLeft(position + VECTOR2(0, 0));
			position.x += push;
			push = s->IsWallLeft(position + VECTOR2(0, 39));
			position.x += push;
		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			position.x += speed;//右
			//右に壁があるか調べる
			int push = s->IsWallRight(position + VECTOR2(39, 0));
			position.x -= push;
			push = s->IsWallRight(position + VECTOR2(39, 39));
			position.x -= push;
		}

		//ジャンプ
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			if (prevJumpKey == false)
			{
				if (onGround == true)
				{
					//2マス分飛ぶ velocity:速度
					velocity = V0;//ジャンプ　上向きの力 "初速を決める"
				}
			}
			prevJumpKey = true;
		}
		else
		{
			prevJumpKey = false;
		}
	}
	

	//重力
	position.y += velocity;//座標には速度を足す
	velocity += Gravity;//下向きの力　速度には重力を足す
	onGround = false;


	//下に壁があるか調べる
	if (velocity >= 0)// velocity:速度
	{
		int push = s->IsWallDown(position + VECTOR2(0, 40)); //一個下を見るので40
		if (push > 0)	//地面に触れたので
		{
			velocity = 0;			//地面に触ったら速度を0に
			position.y -= push - 1; //地面の上に押し返す	1個下を見るのでpush-1
			onGround = true;		//接地してる
		}
		push = s->IsWallDown(position + VECTOR2(39, 40));	 //一個下を見る一個下を見るので40
		if (push > 0)	//地面に触れたので
		{
			velocity = 0;			//地面に触ったら速度を0に
			position.y -= push - 1; //地面の上に押し返す	1個下を見るのでpush-1
			onGround = true;		//接地してる
		}
	}
	//上に壁があるか調べる
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
	

	//プレイヤーに合わせてスクロール(進行)
	if (position.x - s->scroll > 400) //プレイヤーの座標が400以上
	{
		s->scroll = position.x - 400; //スクロール速度をプレイヤーに合わせる
	}
	//プレイヤーに合わせてスクロール(後退)
	if (position.x - s->scroll < 300) //プレイヤーの座標が300以下
	{
		s->scroll = position.x - 300; //スクロール速度をプレイヤーに合わせる
	}

	if (s->IsGoal(position + VECTOR2(20, 20))) //ゴールは左上でなく中心で（右に20,下に20ずれる）
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