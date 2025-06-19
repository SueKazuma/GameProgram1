#include "BallManager.h"
#include "Ball.h"

void BallManager::Update()
{
	std::list<Ball*>balls = FindGameObjects<Ball>(); // ���X�g�Ƀ{�[�����i�[�iObject"s"��Ball�C���X�^���X�S�������j
	for (Ball* b1 : balls) 
	{
		for (Ball* b2 : balls)
		{
			if (b1 == b2) 
			{
				continue;
			}
			b1->HitOtherBall(b2);
			// b1����b2�ւ̓����蔻��
		}
	}
}
