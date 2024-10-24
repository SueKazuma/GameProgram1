#include "Stage.h"
#include "Player.h"
#include "Coin.h"

//const:書き換えられない定数
//直接数字を書くと人格否定される
//数字ではなく文字で書く
const int WIDTH = 12;
const int HIGHT = 8;
const int CHIP_SIZE = 40;

int map[HIGHT][WIDTH] = 
{
	{1,9,0,1,1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,0,1,0,0,0,0},
	{1,0,1,0,0,1,0,1,0,2,0,1},
	{1,0,1,0,2,2,2,2,2,2,0,1},
	{1,0,1,0,0,0,0,0,1,1,1,1},
	{1,0,1,0,1,0,1,1,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1,2,1},
	{1,1,1,1,1,1,1,1,1,1,1,1},
};


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
}

Stage::~Stage()
{
	
}

void Stage::Draw()
{
	//x,y,切り抜き,切り抜き,40,40
	for (int j = 0; j < HIGHT; j++)//縦「j」
	{
		int y = j * CHIP_SIZE + 100;
		for (int i = 0; i < WIDTH; i++)//幅「i」
		{
			int x = i * CHIP_SIZE + 100;
			if (map[j][i] == 1)//レンガ
			{
				DrawRectGraph(x, y, CHIP_SIZE*0, CHIP_SIZE*1, 40, 40, hImage, TRUE);
			}
			//else if (map[j][i] == 2)//コイン
			//{
			//DrawRectGraph(x, y, CHIP_SIZE*3, CHIP_SIZE*0, 40, 40, hImage, TRUE);
			//}
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
