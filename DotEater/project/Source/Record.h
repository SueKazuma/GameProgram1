#pragma once

// クラス：処理＆データをまとめて処理
// データはprivateで。外に通すなら関数を通して値だけ
// 外から操作する場合でも、直接変数に代入させない。(関数を用いる)

// コンストラクタ：初期化
// 　デストラクタ：後片付け(newしたもの、素材をdelete)
class Record
{


public:
	int GetX() { return x; }			// ゲッター関数：読み取り専用
	bool IsDead() { return life <= 0; } // life変数は見せないけど、情報はあげる

	void LifeMax() { life = 500; }		// lifeを操作する関数
private:
	float x; // private：外から書き換えさせない
	int life;
};

