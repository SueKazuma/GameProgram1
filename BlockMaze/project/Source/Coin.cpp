#include "Coin.h"
#include "Player.h"
#include "Stage.h"

Coin::Coin()
{
	//コンストラクタで絵をロード
	hImage = LoadGraph("data/image/parts.png");
	got = false;
}

Coin::~Coin()
{
	DeleteGraph(hImage);
}

void Coin::Update()
{
	if (got) //取られたら
	{
		position.y += v;//浮遊感与えちゃったか…
		v += 9.8f / 60; // 重力/60フレーム

		counter -= 1;
		if (counter == 0)
		{
			DestroyMe();//死ぬしかないじゃない！
		}
		return;//終わり！閉廷！以上！皆解散！
	}
	
	//取られる前
		//当たり判定
		Player* p = FindGameObject<Player>();//インスタンス：Playerを探す
		VECTOR2 playerPos = p->position;//playerPosにplayerのpositionを入れる
		//当たり判定："playerPos"と"position"が当たったら
		if (CircleHit(position, playerPos, 40))
		{
			got = true;//取られた！
			counter = 20;//死へのカウンター２０フレーム
			v = -2.5;//跳ねる力(上方向なので「-」符号)
		}
}

void Coin::Draw()
{
	Stage* s = FindGameObject<Stage>();
	DrawRectGraph(position.x - s->scroll, position.y, 40 * 3, 40 * 0, 40, 40, hImage, TRUE);
}


//放物線（二次方程式）　
//[数学]　y = ax ^ 2 + bx + c;	　		←まぁ、使いませんケド！
//[物理]　v = v0 + at／v = v0 + gt　	←ｖ:速 = v0:初速 + gt:初速　ｔ:時間
//[プログラム]　x += v; v += g;