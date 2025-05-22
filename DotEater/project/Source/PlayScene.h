#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// �Q�[���v���C�̃V�[���𐧌䂷��
/// </summary>
class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
	bool CanPlay();
private:
	enum State { // �Q�[�����
		S_READY = 0,
		S_PLAY,
		S_TIMEUP,
		S_CLEAR,
	};
	State state;
};
