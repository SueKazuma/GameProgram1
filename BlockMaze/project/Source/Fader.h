#pragma once
#include "../Library/gameObject.h"

class Fader : public GameObject
{
public:
	Fader();
	~Fader();
	void Update() override;
	void Draw() override;

	void FadeOut(unsigned int color, float time);
	bool IsFinish();

	float alpha;			//�s�����x
	unsigned int fadeColor; //�F
	float fadeTime;			//�t�F�[�h�A�E�g����
	float timer;			//���ۂ̌o�ߎ���
};