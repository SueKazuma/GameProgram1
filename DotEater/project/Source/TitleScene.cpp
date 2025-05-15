#include "TitleScene.h"
#include <fstream>

TitleScene::TitleScene()
{
	std::ifstream ifs("data/stage00.csv"); // CSVファイルを開く
	std::string str; // 文字列を用意
	getline(ifs, str);// ファイルから１行読む関数
	
	int n = str.find(',');//カンマの文字の位置を返す関数
	std::string s1 = str.substr(0,n); //0～n文字切り出す関数
	int d = stoi(s1); //文字列をintに変える
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255,255,255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
