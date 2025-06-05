#include "Ball.h"
#include "Screen.h"

Ball::Ball(int num, VECTOR3 pos)
{
	hImage = LoadGraph("data/textures/billiyard.png");

	number = num;
	position = pos;
	velocity = VECTOR3(0, 0, 0);

	catched = false;
}

Ball::~Ball()
{
}

void Ball::Update()
{

	if (catched) 
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT)==0)
		{
			// 左クリックを離したとき
			int x, y;
			GetMousePoint(&x, &y);
			velocity =  VECTOR3(catchX-x,catchY-y,0)/20.0f;
			catched = false;
		}
	}
	else 
	{
		if (GetMouseInput() & MOUSE_INPUT_LEFT)
		{
			// 左クリック押したときの座標を取っておく
			catched = true;
			GetMousePoint(&catchX, &catchY);
		}
	}

	position += velocity;
	
	// レフレクション
	if (position.y >= Screen::HEIGHT-28) 
	{
		//下の反射
		velocity.y = -velocity.y;
	}
	if (position.y < 0 + 28)
	{
		//上の反射
		velocity.y = -velocity.y;
	}

	if (position.x >= Screen::WIDTH - 28)
	{
		//右の反射
		velocity.x = -velocity.x;
	}
	if (position.x < 0 + 28)
	{
		//左の反射
		velocity.x = -velocity.x;
	}

	float len = velocity.Size(); // ベクトルの長さを求める
	len -= 0.01f; // 長さを一定値減らす
	
	if (len <= 0.0f) // 長さが0以下なら、velocityは(0,0,0)
	{
		velocity = VECTOR3(0, 0, 0);
	}
	else // 0より上ならvelocityをその長さにする
	{
		velocity = velocity.Normalize() * len;
	}
	


}

void Ball::Draw()
{
	int x = (number - 1) % 4;
	int y = (number - 1) / 4;

	DrawRectGraph(position.x-32, position.y-32, x * 64, y * 64, 64, 64, hImage, TRUE);
}
