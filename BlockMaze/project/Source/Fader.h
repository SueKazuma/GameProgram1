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

	float alpha;			//不透明度
	unsigned int fadeColor; //色
	float fadeTime;			//フェードアウト時間
	float timer;			//実際の経過時間
};