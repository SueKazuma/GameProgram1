#pragma once

// �N���X�F�������f�[�^���܂Ƃ߂ď���
// �f�[�^��private�ŁB�O�ɒʂ��Ȃ�֐���ʂ��Ēl����
// �O���瑀�삷��ꍇ�ł��A���ڕϐ��ɑ�������Ȃ��B(�֐���p����)

// �R���X�g���N�^�F������
// �@�f�X�g���N�^�F��Еt��(new�������́A�f�ނ�delete)
class Record
{


public:
	int GetX() { return x; }			// �Q�b�^�[�֐��F�ǂݎ���p
	bool IsDead() { return life <= 0; } // life�ϐ��͌����Ȃ����ǁA���͂�����

	void LifeMax() { life = 500; }		// life�𑀍삷��֐�
private:
	float x; // private�F�O���珑�����������Ȃ�
	int life;
};

