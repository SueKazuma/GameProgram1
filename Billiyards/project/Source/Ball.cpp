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
	// 16��(����)�̂�
	if (number == 16) 
	{
		if (catched)
		{
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0)
			{
				// ���N���b�N�𗣂����Ƃ�
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
				// ���N���b�N�������Ƃ��̍��W������Ă���
				catched = true;
				GetMousePoint(&catchX, &catchY);
			}
		}

	}

	position += velocity;
	
	/*
	// ���t���N�V����
	if (position.y >= Screen::HEIGHT-28) 
	{
		//���̔���
		velocity.y = -velocity.y;
	}
	else if (position.y < 0 + 28)
	{
		//��̔���
		velocity.y = -velocity.y;
	}

	if (position.x >= Screen::WIDTH - 28)
	{
		//�E�̔���
		velocity.x = -velocity.x;
	}
	else if (position.x < 0 + 28)
	{
		//���̔���
		velocity.x = -velocity.x;
	}
	*/
	// �E�H�[�����t���N�V����
	if (position.y < 0 + 28 || position.y >= Screen::HEIGHT - 28)
	{
		//�㉺�̔���
		velocity.y = -velocity.y;
	}
	if (position.x < 0 + 28 || position.x >= Screen::WIDTH - 28)
	{
		//���E�̔���
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

void Ball::AddForce(VECTOR3 force) 
{
	// ����ɓn��(�������瑊��)
	addVelocity += force;
}

void Ball::HitOtherBall(Ball* other)
{
	//1:�������Ă��邩���ׂ�
	VECTOR3 v = other->GetPosition() - position; // �����Ƒ���̃x�N�g��
	//��������
	if (v.Size() < 60.0f)
	{
		// �߂荞�ݖh�~
		float pushLen = 60.0f - v.Size();
		position -= v.Normalize() * pushLen;

		//2:�͂�������
		VECTOR3 a = velocity;		// a �͎����̈ړ��x�N�g��
		VECTOR3 b = v.Normalize();  // b �͎���������x�N�g���̒����P
		float len = VDot(a, b);		// ����(����ɗ^�����)�����߂�
		// ����ɓn���x�N�g��
		// �E����������������
		// �E������len
		other->AddForce(b * len); // �ǂ������Ȃ��ꍇ��AddForce�����Ō��[-b*len*2f]����(����p)
		// ������velocity����n����������
		AddForce(b * (-len));
	}
}
