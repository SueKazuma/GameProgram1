#include "TitleScene.h"
#include <fstream>
#include "Record.h"

Record* rp;

class Base // 基底クラス
{
public:
	Base(){ OutputDebugString("BASE\n"); }
	~Base(){ OutputDebugString("~BASE\n"); }
	virtual void F1() { OutputDebugString("BASE::F1\n"); }
	virtual void F2() { OutputDebugString("BASE::F2\n"); }
	void F3() { OutputDebugString("BASE::F3\n"); }
};

class Sub : public Base // 派生クラス
{
public:
	Sub() { OutputDebugString("SUB\n"); }
	~Sub() { OutputDebugString("~SUB\n"); }
	void Update() { F1(); F2(); F3(); } // privateはNG。protectedは継承なら弄れる。

	void F1() override { OutputDebugString("SUB::F1\n"); }
	void F3() { OutputDebugString("SUB::F3\n"); }
};

Sub* sub;
Base* base;

TitleScene::TitleScene()
{
	// 基底クラスにvirtial付ける
	// 派生はoverride書かない

	// インスタンス：クラスの実体化。変数の宣言的なもの。
	Record r;
	Record r2; // { }で勝手に消えるインスタンス

	rp = new Record(); // ヒープに作られるインスタンス
	
	sub = new Sub();
	sub->F1();
	sub->F2();
	sub->F3();

	base = new Sub();
	base->F1();
	base->F2();
	base->F3();
}

TitleScene::~TitleScene()
{
	delete rp;

	delete sub;
	delete base;
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255,255,255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
