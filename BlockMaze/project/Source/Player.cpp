#include "Player.h"
#include "Stage.h"

Player::Player()
{
	hImage = LoadGraph("data/image/chara.png");
	position.x = 0;
	position.y = 0;

	speed = 2;
}

Player::~Player()
{
	DeleteGraph(hImage);
}

void Player::Update()
{
	Stage* s = FindGameObject<Stage>();

	if (CheckHitKey(KEY_INPUT_W)) 
	{
		position.y -= speed;//ã
		//ã‚É•Ç‚ª‚ ‚é‚©’²‚×‚é
		int push = s->IsWallUp(position + VECTOR2(0, 0));
		position.y += push;
		push = s->IsWallUp(position + VECTOR2(39, 0));
		position.y += push;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		position.y += speed;//‰º
		//‰º‚É•Ç‚ª‚ ‚é‚©’²‚×‚é
		int push = s->IsWallDown(position + VECTOR2(0, 39));
		position.y -= push;
		push = s->IsWallDown(position + VECTOR2(39, 39));
		position.y -= push;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		position.x -= speed;//¶
		//¶‚É•Ç‚ª‚ ‚é‚©’²‚×‚é
		int push = s->IsWallLeft(position + VECTOR2(0, 0));
		position.x += push;
		push = s->IsWallLeft(position + VECTOR2(0, 39));
		position.x += push;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		position.x += speed;//‰E
		//‰E‚É•Ç‚ª‚ ‚é‚©’²‚×‚é
		int push = s->IsWallRight(position + VECTOR2(39, 0));
		position.x -= push;
		push = s->IsWallRight(position + VECTOR2(39, 39));
		position.x -= push;
	}
}

void Player::Draw()
{
	DrawRectGraph(position.x, position.y, 0, 0, 40, 40, hImage, TRUE);
}
