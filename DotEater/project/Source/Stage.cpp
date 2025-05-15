#include "Stage.h"
#include <assert.h>
#include <vector>
#include "Player.h"
#include "Coin.h"
#include "CsvReader.h"
using namespace std;

Stage::Stage()
{
	//CSVからマップ作り
	CsvReader* csv = new CsvReader("data/stage00.csv");
	for (int z = 0; z < csv->GetLines(); z++) 
	{
		vector<int> mapLine;
		for (int x = 0; x < csv->GetColumns(z); x++)
		{
			mapLine.push_back(csv->GetInt(z, x));
		}
		maps.push_back(mapLine);
	}

	hModel = MV1LoadModel("data/models/RedBrickBlock.mv1");
	assert(hModel > 0);

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	//SetLightDirection(VGet(0, -1, 0));//下向きなライト

	//mapsの"2"にホラーマンが生まれる！
	for (int z = 0; z < maps.size(); z++)
	{
		for (int x = 0; x < maps[z].size(); x++)
		{
			if (maps[z][x] == 2)
			{
				new Player(VGet(x * 100.0f, 0, z * -100.0f));
			}
			else if (maps[z][x] == 3)
			{
				new Coin(VGet(x * 100.0f, 50.0f, z * -100.0f));
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