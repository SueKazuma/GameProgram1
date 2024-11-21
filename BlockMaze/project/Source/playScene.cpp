#include "playScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"
#include <DxLib.h>
#include "Stage.h"
#include "Player.h"

PlayScene::PlayScene()
{
	Stage* s = Instantiate<Stage>();
	//�X�e�[�W��`�����Ԃ�10�ɂ��Ă�������
	SetDrawOrder(s, 10);
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	//�B���L�[
	if (CheckHitKey(KEY_INPUT_T)) 
	{
		SceneManager::ChangeScene("TitleScene");
	}
	SceneBase::Update();
}

void PlayScene::Draw()
{
	SceneBase::Draw();
}
