#include "playScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"
#include <DxLib.h>
#include "Stage.h"
#include "Fader.h"

PlayScene::PlayScene()
{
	Stage* s = Instantiate<Stage>();
	//�X�e�[�W��`�����Ԃ�10�ɂ��Ă�������
	SetDrawOrder(s, 10);

	Instantiate<Fader>();
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
