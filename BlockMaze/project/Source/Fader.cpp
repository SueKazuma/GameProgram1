#include "Fader.h"
#include "config.h"
//フェードイン＆フェードアウト
//暗所↔明所　ダメージ
//一番手前のレイヤーの"不"透明度を設定する

Fader::Fader()
{
	alpha = 0.0f;
	fadeTime = 0.0f;
	timer = 0.0f;
}

Fader::~Fader()
{
}

void Fader::Update()
{
	//終了時間を超えないように
	if (timer < fadeTime)
	{
		//1秒ずつ足している(DeltaTimeでも可能?)
		timer += 1.0f / 60.0f;
		//alphaを求める
		alpha = 255 / fadeTime * timer;


	}
}

void Fader::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha); //透過する
	//四角を表示(左上,右下、色(R,G,B)、塗りつぶし)
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, fadeColor, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //透過しない
}

//不透明になっていく
void Fader::FadeOut(unsigned int color, float time)
{
	//リセットマンユニバース
	alpha = 0.0f;
	timer = 0.0f;
	//代入する
	fadeColor = color;
	fadeTime = time;
}

//
bool Fader::IsFinish()
{
	//fadeTimeを超えたら
	if (timer >= fadeTime)
	{
		return true;
	}
	return false;
}
