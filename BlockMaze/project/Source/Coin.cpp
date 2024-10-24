#include "Coin.h"
#include "Player.h"

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
		position.y -= 3;//浮遊感与えちゃったか…
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
		}
}

void Coin::Draw()
{
	DrawRectGraph(position.x, position.y,   40 * 3, 40 * 0,   40, 40, hImage, TRUE);
}
