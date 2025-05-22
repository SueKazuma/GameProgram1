#include "ReadyGo.h"

ReadyGo::ReadyGo()
{
	hReady = LoadGraph("data/images/ready.png");
	hGo = LoadGraph("data/images/go.png");

	timer = 1.0f;
}

ReadyGo::~ReadyGo()
{
	DeleteGraph(hReady);
	DeleteGraph(hGo);
}

void ReadyGo::Update()
{
	//Ready‚ğ‚P•b•\¦@Go‚ğ0.5
	timer -= Time::DeltaTime();

	if (timer < -0.5f)
	{
		DestroyMe();

	}

}

void ReadyGo::Draw()
{
	if (timer > 0.0f)
	{
		DrawGraph(300, 300, hReady, TRUE);
	}
	else
	{
		DrawGraph(300, 300, hGo, TRUE);
	}
}

bool ReadyGo::TimeEnd()
{
	return timer <=0.0f; // ğŒ’B¬‚Åtrue
}
