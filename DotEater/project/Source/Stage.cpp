#include "Stage.h"
#include <assert.h>
#include <vector>
#include "Player.h"
using namespace std;


vector<vector<int>> maps = {
	{ 2,1,0,1,1 },
	{ 0,1,1,0,1 },
	{ 0,1,1,0,1 },
};


Stage::Stage()
{
	hModel = MV1LoadModel("data/models/RedBrickBlock.mv1");
	assert(hModel > 0);

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	SetLightDirection(VGet(0, -1, 0));//下向きなライト

	//mapsの"2"にホラーマンが生まれる！
	for (int z = 0; z < maps.size(); z++)
	{
		for (int x = 0; x < maps[z].size(); x++)
		{
			if (maps[z][x] == 2)
			{
				new Player(VGet(x * 100.0f, 0, z * -100.0f));
			}
		}
	}
}

Stage::~Stage()
{
}

void Stage::Draw()
{
	//[x(横)⇀z(縦)]の順で計算していましてよ！
	for (int z = 0; z < maps.size(); z++)
	{
		for (int x = 0; x < maps[z].size(); x++)
		{
			if (maps[z][x] == 1)
			{
				MV1SetPosition(hModel, VGet(x * 100.0f, 0, z * -100.0f));
				MV1DrawModel(hModel);
			}
		}
	}
	
}