#pragma once
//GoalText.h
#include "../Library/gameObject.h"

class GoalText :public GameObject
{
public:
	GoalText();
	~GoalText();
	void Update() override;
	void Draw() override;

	float timer;
	bool fadeStarted;//�t�F�[�h�A�J�n�B�B�B�B�B
};
