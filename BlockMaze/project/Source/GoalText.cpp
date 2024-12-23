#include "GoalText.h"
#include "../Library/time.h"
#include "Fader.h"

GoalText::GoalText()
{
	timer = 0.0f;
	fadeStarted = false;
}

GoalText::~GoalText()
{
}

int score = 100;


void GoalText::Update()
{
	//フェード開始したら
	if (fadeStarted)
	{
		Fader* f = FindGameObject<Fader>();
		//Finish実行
		if (f->IsFinish())
		{
			SceneManager::ChangeScene("TitleScene");
		}
		return; // フェード中なら以下の処理は行わない
	}

	//Time::DeltaTime();：秒で測れるためＰＣのフレーム性能に左右されない
	timer += Time::DeltaTime();


	if (timer >= 2.5f)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			Fader* f = FindGameObject<Fader>();
			f->FadeOut(GetColor(0, 0, 0), 0.5f);
			fadeStarted = true; // フェード開始
			
		}
	}

}

void GoalText::Draw()
{
	
	//現在のフォントサイズ
	int size = GetFontSize();

	//ゴールの文字を大きく
	SetFontSize(50);
	DrawString(200, 200, "FINISH! ", GetColor(255, 255, 127));				//(x,y,文字列,色)

	if (timer >= 1.0f) //１秒超えたらずっと表示
	{
		SetFontSize(25);
		//(x,y,色,文字列,変わる文字列)   「%d」を置き換える
		//「%6d」 ：６桁用意する　（if文でカンストさせればオーバーしない）
		//「%06d」：６桁用意する　空白を０で埋める
		//「d」：「ｄ」は１０進数を意味する
		//「%06d%%」：「ｎ％」表示出来る
		DrawFormatString(200, 300, GetColor(255, 255, 255), "SCORE:%06d", score);
	}
	if (timer >= 2.0f) //１秒超えたらずっと表示
	{
		DrawString(200, 500, "スペースキーを押して終了 ", GetColor(255, 255, 255));
	}

	//元のフォントサイズに戻す
	SetFontSize(size);
}
