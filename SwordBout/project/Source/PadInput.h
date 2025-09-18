#pragma once
#include "../Library/GameObject.h"

class PadInput : public GameObject
{
public:
	PadInput(int id);
	~PadInput();
	void Update() override;
	void Draw() override;

	float LStickX();
	float LStickY();
	float RStickX();
	float RStickY();
	VECTOR2 LStickVec();	 // �c������
	VECTOR2 RStickVec();	 // �c������

	bool Press(int id);	  	 // �����Ă�
	bool OnPush(int id);	 // ������
	void Reset();			 // 
private:
	int padId;
	XINPUT_STATE input;
	static  const int MAX= 32767;
	static const int ZERO_RANGE = MAX / 5; // MAX/5�ȉ��Ȃ�O�Ɣ���

	unsigned char prevButtons[16]; // �O�̃{�^��
};

