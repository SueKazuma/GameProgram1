#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// 3D���f�� �Q�[���I�u�W�F�N�g
/// 
/// 3D���f����\������
/// </summary>

class Model : public GameObject
{
public:
	Model();
	~Model();
	void Update() override;
	void Draw() override;
	//int GethModel() { return hModel; }�@���Ȃ�R��

private: // �ϐ��͊�{���ׂăv���C�x�[�g�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I
	int hModel;
	VECTOR rotation;
};