#include "playScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"
#include <DxLib.h>
#include "Stage.h"
#include "Player.h"

PlayScene::PlayScene()
{
	Stage* s = Instantiate<Stage>();
	//ステージを描く順番を10にしてください
	SetDrawOrder(s, 10);
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	//隠しキー
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
