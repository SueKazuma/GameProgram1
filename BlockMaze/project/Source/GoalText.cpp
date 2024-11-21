#include "GoalText.h"
#include "../Library/time.h"

GoalText::GoalText()
{
	timer = 0.0f;
}

GoalText::~GoalText()
{
}

int score = 100;


void GoalText::Update()
{

	//Time::DeltaTime();�F�b�ő���邽�߂o�b�̃t���[�����\�ɍ��E����Ȃ�
	timer += Time::DeltaTime();


	if (timer >= 2.5f)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			SceneManager::ChangeScene("TitleScene");
		}
	}

}

void GoalText::Draw()
{
	
	//���݂̃t�H���g�T�C�Y
	int size = GetFontSize();

	//�S�[���̕�����傫��
	SetFontSize(50);
	DrawString(200, 200, "FINISH! ", GetColor(255, 255, 127));				//(x,y,������,�F)

	if (timer >= 1.0f) //�P�b�������炸���ƕ\��
	{
		SetFontSize(25);
		//(x,y,�F,������,�ς�镶����)   �u%d�v��u��������
		//�u%6d�v �F�U���p�ӂ���@�iif���ŃJ���X�g������΃I�[�o�[���Ȃ��j
		//�u%06d�v�F�U���p�ӂ���@�󔒂��O�Ŗ��߂�
		//�ud�v�F�u���v�͂P�O�i�����Ӗ�����
		//�u%06d%%�v�F�u�����v�\���o����
		DrawFormatString(200, 300, GetColor(255, 255, 255), "SCORE:%06d", score);
	}
	if (timer >= 2.0f) //�P�b�������炸���ƕ\��
	{
		DrawString(200, 500, "�X�y�[�X�L�[�������ďI�� ", GetColor(255, 255, 255));
	}

	//���̃t�H���g�T�C�Y�ɖ߂�
	SetFontSize(size);
}
