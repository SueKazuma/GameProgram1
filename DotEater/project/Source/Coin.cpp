#include "Coin.h"
#include "Player.h"

Coin::Coin(VECTOR pos)
{
	hModel = MV1LoadModel("data/models/Coin.mv1");
	position = pos;

	gotten = false;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	Player* p = FindGameObject<Player>();
	VECTOR pPos = p->GetPosition(); // プレイヤーの足元の座標

	pPos += VGet(0.0f, 50.0f, 0.0f); //プレイヤー座標を同じ高さに
	
	
	if (gotten)
	{
		//行先-今いるとこ
		VECTOR CtoP = (pPos - position);
		CtoP = VNorm(CtoP) * 5;
		position += CtoP;
		//playerにちかづく
		float diff = VSize(pPos - position); // 2点間の距離
		if (diff < 10.0f) // 当たっている
		{
			DestroyMe();
		}
	}
	else
	{
		float diff = VSize(pPos - position); // 2点間の距離
		if (diff < 120.0f) // 当たっている
		{
			gotten = true;
		}
	}

	

	
}
