#pragma once
#include "../Library/sceneBase.h"
#include "Player.h"

class PlayScene : public SceneBase {
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
};