#include "TitleScene.h"
#include <fstream>

TitleScene::TitleScene()
{
	std::ifstream ifs("data/stage00.csv"); // CSV�t�@�C�����J��
	std::string str; // �������p��
	getline(ifs, str);// �t�@�C������P�s�ǂފ֐�
	
	int n = str.find(',');//�J���}�̕����̈ʒu��Ԃ��֐�
	std::string s1 = str.substr(0,n); //0�`n�����؂�o���֐�
	int d = stoi(s1); //�������int�ɕς���
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
