#include "BootScene.h"
#include "PadInput.h"

BootScene::BootScene()
{
	new PadInput(DX_INPUT_PAD1);
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SceneManager::ChangeScene("TITLE"); // �N�����I�������Title��\��
}

void BootScene::Draw()
{
}
