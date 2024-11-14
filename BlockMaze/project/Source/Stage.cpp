#include "Stage.h"
#include "Player.h"
#include "Coin.h"

//#include：このファイルデータ使ってくださいね！
const int CHIP_SIZE = 40;
#include "stage1.h"

Stage::Stage()
{
	hImage = LoadGraph("data/image/parts.png");

	//9を探して、Playerを置く
	for (int j = 0; j < HIGHT; j++) //「j」縦
	{
		for (int i = 0; i < WIDTH; i++)//「i」横
		{
			if (map[j][i] == 9)//プレイヤー生成
			{
				Player* p = Instantiate<Player>();
				p->position.x = CHIP_SIZE * i + 100;
				p->position.y = CHIP_SIZE * j + 100;
			}
			if (map[j][i] == 2)//コイン生成
			{
				Coin* c = Instantiate<Coin>();
				c->position.x = CHIP_SIZE * i + 100;
				c->position.y = CHIP_SIZE * j + 100;
			}
		}
	}
	scroll = 0;
}

Stage::~Stage()
{
	
}

void Stage::Draw()
{

	//x,y,切り抜き,切り抜き,40,40
	for (int j = 0; j < HIGHT; j++)		//縦「j」
	{
		int y = j * CHIP_SIZE + 100;
		for (int i = 0; i < WIDTH; i++)	//幅「i」
		{
			int x = i * CHIP_SIZE + 100;
			if (map[j][i] == 1)		   //赤レンガ
			{
				DrawRectGraph(x - scroll, y, CHIP_SIZE * 0, CHIP_SIZE * 1, 40, 40, hImage, TRUE);
			}
			else if (map[j][i] == 8)   //ゴール
			{
				DrawRectGraph(x - scroll, y, CHIP_SIZE*4, CHIP_SIZE*0, 40, 40, hImage, TRUE);
			}
		}
	}


}

int Stage::IsWallRight(VECTOR2 pos)//posにはplayer座標が入る
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 1)
	{
		//めり込んだ分押し返す
		//★(int)少数だけどintとして扱う
		int push = ((int)pos.x - 100) % 40 + 1;//0なら1 1なら2
		return push;
	}
	return 0;
}

int Stage::IsWallLeft(VECTOR2 pos)
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 1)
	{
		//めり込んだ分押し返す
		//★(int)少数だけどintとして扱う
		int push = 40 - ((int)pos.x - 100) % 40;//39なら1 38なら2
		return push;
	}
	return 0;
}

int Stage::IsWallDown(VECTOR2 pos)
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 1)
	{
		//めり込んだ分押し返す
		//★(int)少数だけどintとして扱う
		int push = ((int)pos.y - 100) % 40 + 1;
		return push;
	}
	return 0;
}

int Stage::IsWallUp(VECTOR2 pos)
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 1)
	{
		//めり込んだ分押し返す
		//★(int)少数だけどintとして扱う
		int push = 40 - ((int)pos.y - 100) % 40;//39なら1 38なら2
		return push;
	}
	return 0;
}

bool Stage::IsGoal(VECTOR2 pos)
{
	//「マップチップ→座標」の逆、「座標→マップチップ」
	int i = (pos.x - 100) / 40;
	int j = (pos.y - 100) / 40;
	if (map[j][i] == 8)
	{
		return true;
	}
	return false;
}
