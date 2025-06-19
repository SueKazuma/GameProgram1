#include "BallManager.h"
#include "Ball.h"

void BallManager::Update()
{
	std::list<Ball*>balls = FindGameObjects<Ball>(); // リストにボールを格納（Object"s"でBallインスタンス全部発見）
	for (Ball* b1 : balls) 
	{
		for (Ball* b2 : balls)
		{
			if (b1 == b2) 
			{
				continue;
			}
			b1->HitOtherBall(b2);
			// b1からb2への当たり判定
		}
	}
}
