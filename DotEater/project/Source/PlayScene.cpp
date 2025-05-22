#include "PlayScene.h"
#include "Axis.h"
#include "Camera.h"
#include "Stage.h"
#include "ReadyGo.h"
#include "PlayTime.h"

// �v���C���ԂP�O�b�Ń^�C���A�b�v�I

PlayScene::PlayScene()
{
	new Axis();
	new Camera();
	new Stage();
	new ReadyGo();
	

	state = S_READY;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	

	if (state == S_READY) 
	{
		ReadyGo* ready = FindGameObject<ReadyGo>();
		if (ready->TimeEnd()) 
		{
			state = S_PLAY;
			new PlayTime();
		}
	}
	else if (state == S_PLAY)
	{
		PlayTime* playTime = FindGameObject<PlayTime>();
		if (playTime->TimeUp())
		{
			state = S_TIMEUP;
		}
	}



	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}

bool PlayScene::CanPlay()
{
	return state == S_PLAY; // ��v������true
}
