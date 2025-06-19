#include "Ball.h"
#include "Screen.h"

Ball::Ball(int num, VECTOR3 pos)
{
	hImage = LoadGraph("data/textures/billiyard.png");

	number = num;
	position = pos;
	velocity = VECTOR3(0, 0, 0);
	addVelocity = VECTOR3(0, 0, 0);

	catched = false;
}

Ball::~Ball()
{
}

void Ball::Update()
{
	velocity += addVelocity;
	addVelocity = VECTOR3(0, 0, 0);
	// 16番(白球)のみ
	if (number == 16) 
	{
		if (catched)
		{
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0)
			{
				// 左クリックを離したとき
				int x, y;
				GetMousePoint(&x, &y);
				velocity = VECTOR3(catchX - x, catchY - y, 0) / 20.0f;
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

	}

	position += velocity;
	
	/*
	// リフレクション
	if (position.y >= Screen::HEIGHT-28) 
	{
		//下の反射
		velocity.y = -velocity.y;
	}
	else if (position.y < 0 + 28)
	{
		//上の反射
		velocity.y = -velocity.y;
	}

	if (position.x >= Screen::WIDTH - 28)
	{
		//右の反射
		velocity.x = -velocity.x;
	}
	else if (position.x < 0 + 28)
	{
		//左の反射
		velocity.x = -velocity.x;
	}
	*/
	// ウォールリフレクション
	if (position.y < 0 + 28 || position.y >= Screen::HEIGHT - 28)
	{
		//上下の反射
		velocity.y = -velocity.y;
	}
	if (position.x < 0 + 28 || position.x >= Screen::WIDTH - 28)
	{
		//左右の反射
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

void Ball::AddForce(VECTOR3 force) 
{
	// 相手に渡す(自分から相手)
	addVelocity += force;
}

void Ball::HitOtherBall(Ball* other)
{
	//1:当たっているか調べる
	VECTOR3 v = other->GetPosition() - position; // 自分と相手のベクトル
	//当たった
	if (v.Size() < 60.0f)
	{
		// めり込み防止
		float pushLen = 60.0f - v.Size();
		position -= v.Normalize() * pushLen;

		//2:力を加える
		VECTOR3 a = velocity;		// a は自分の移動ベクトル
		VECTOR3 b = v.Normalize();  // b は自分→相手ベクトルの長さ１
		float len = VDot(a, b);		// 内積(相手に与える力)を求める
		// 相手に渡すベクトル
		// ・向きが自分→相手
		// ・長さはlen
		other->AddForce(b * len); // 壁が動かない場合はAddForceせず最後に[-b*len*2f]する(反作用)
		// 自分のvelocityから渡した分引く
		AddForce(b * (-len));
	}
}
