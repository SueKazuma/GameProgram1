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
	VECTOR pPos = p->GetPosition();  // プレイヤーの足元の座標
	pPos += VGet(0.0f, 50.0f, 0.0f); //プレイヤー座標を同じ高さに
	
	
	if (gotten)
	{
		homingUpdate();
#if false
		// 行先 - 現在地
		//１．コイン→プレイヤーのベクトル
		VECTOR CtoP = (pPos - position);
		//２．ベクトルの長さが５のものを作る
		CtoP = VNorm(CtoP) * 5;
		//３．コインの座標に加える
		position += CtoP;
		//４．コインとプレイヤーの距離が１０以下になったら
		float diff = VSize(pPos - position); // 2点間の距離
		if (diff < 10.0f) // 当たっている
		{
			DestroyMe();
		}
#endif
	}
	else
	{
		float diff = VSize(pPos - position); // 2点間の距離
		if (diff < 120.0f) // コインに当たっている
		{
			gotten = true;
			homingStart();
		}
	}
	
}

void Coin::homingStart() // 奥に飛ばす
{
	Player* p = FindGameObject<Player>();
	VECTOR pPos = p->GetPosition();  // プレイヤーの足元の座標
	pPos += VGet(0.0f, 50.0f, 0.0f); //プレイヤー座標を同じ高さに
	VECTOR v = pPos - position;
	velocity = VNorm(v) * -10.0f; // 向き×移動速度 つまり"Normalize"は向きだけ取り出す
}

void Coin::homingUpdate() // 消滅
{
	position += velocity;

	Player* p = FindGameObject<Player>();
	VECTOR pPos = p->GetPosition();  // プレイヤーの足元の座標
	pPos += VGet(0.0f, 50.0f, 0.0f); //プレイヤー座標を同じ高さに

	VECTOR v = pPos - position; // 相手へのベクトル
	if (VSize(v) < 20.0f) 
	{
		DestroyMe();
	}

	VECTOR a = VNorm(velocity); // 自分の正面
	VECTOR b = VNorm(v);        // 相手へのベクトルの向き
	float co = VDot(a, b);
	float speed = (co + 1.0f) * 10.0f; // Θが0度なら速く、Θが90度なら遅く
	// coはΘが１～-１になるので、１のとき２０、-１のとき０

	float len = VSize(velocity);	  // 今の長さ
	if (len > speed) // 速スギィ！
	{
		len -= 0.05f;
	}
	else			 // 遅スギィ！
	{
		len += 0.05f;
	}
	velocity = VNorm(velocity) * len;

	VECTOR rightVec = velocity * MGetRotY(90.0f * DegToRad);
	float ip = VDot(rightVec, v); // 内積を求める
	// 速ければ角度を小さく、遅ければ大きく
	float rspeed = (25.0f - len) / 5.0f;
	if (ip > 0) // 右にいる
	{
		velocity = velocity * MGetRotY( rspeed * DegToRad);  // 右旋回
	}
	else
	{
		velocity = velocity * MGetRotY(-rspeed * DegToRad); // 左旋回
	}
}
