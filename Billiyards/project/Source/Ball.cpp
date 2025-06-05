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
			// ���N���b�N�𗣂����Ƃ�
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
			// ���N���b�N�������Ƃ��̍��W������Ă���
			catched = true;
			GetMousePoint(&catchX, &catchY);
		}
	}

	position += velocity;
	
	// ���t���N�V����
	if (position.y >= Screen::HEIGHT-28) 
	{
		//���̔���
		velocity.y = -velocity.y;
	}
	if (position.y < 0 + 28)
	{
		//��̔���
		velocity.y = -velocity.y;
	}

	if (position.x >= Screen::WIDTH - 28)
	{
		//�E�̔���
		velocity.x = -velocity.x;
	}
	if (position.x < 0 + 28)
	{
		//���̔���
		velocity.x = -velocity.x;
	}

	float len = velocity.Size(); // �x�N�g���̒��������߂�
	len -= 0.01f; // ���������l���炷
	
	if (len <= 0.0f) // ������0�ȉ��Ȃ�Avelocity��(0,0,0)
	{
		velocity = VECTOR3(0, 0, 0);
	}
	else // 0����Ȃ�velocity�����̒����ɂ���
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
