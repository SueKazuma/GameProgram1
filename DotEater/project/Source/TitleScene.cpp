#include "TitleScene.h"
#include <fstream>
#include "Record.h"

Record* rp;

class Base // ���N���X
{
public:
	Base(){ OutputDebugString("BASE\n"); }
	~Base(){ OutputDebugString("~BASE\n"); }
	virtual void F1() { OutputDebugString("BASE::F1\n"); }
	virtual void F2() { OutputDebugString("BASE::F2\n"); }
	void F3() { OutputDebugString("BASE::F3\n"); }
};

class Sub : public Base // �h���N���X
{
public:
	Sub() { OutputDebugString("SUB\n"); }
	~Sub() { OutputDebugString("~SUB\n"); }
	void Update() { F1(); F2(); F3(); } // private��NG�Bprotected�͌p���Ȃ�M���B

	void F1() override { OutputDebugString("SUB::F1\n"); }
	void F3() { OutputDebugString("SUB::F3\n"); }
};

Sub* sub;
Base* base;

TitleScene::TitleScene()
{
	// ���N���X��virtial�t����
	// �h����override�����Ȃ�

	// �C���X�^���X�F�N���X�̎��̉��B�ϐ��̐錾�I�Ȃ��́B
	Record r;
	Record r2; // { }�ŏ���ɏ�����C���X�^���X

	rp = new Record(); // �q�[�v�ɍ����C���X�^���X
	
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
