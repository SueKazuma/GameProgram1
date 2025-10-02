#include "Camera.h"
#include "PadInput.h"

namespace 
{
	static float distance = 500.0f; // �L��������̋���
	static float lookHeight = 200.0f; // �����_�̍���
};

Camera::Camera()
{
	GetMousePoint(&prevMouseX, &prevMouseY);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	// ��Pad
	PadInput* pad = FindGameObject<PadInput>();
	float padX = pad->RStickX();
	float padY = pad->RStickY();
	transform.rotation.y += padX * 3.0f * DegToRad;
	transform.rotation.x -= padY * 3.0f * DegToRad;

	#pragma region �J�����ړ�
	// ���E�i�L�[�j
	if (CheckHitKey(KEY_INPUT_RIGHT)) // ��Key
	{
		transform.rotation.y += 3.0f * DegToRad;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT)) // ��Key
	{
		transform.rotation.y -= 3.0f * DegToRad;
	}
	// �㉺�i�L�[�j
	if (CheckHitKey(KEY_INPUT_DOWN)) // ��Key
	{
		transform.rotation.x -= 3.0f * DegToRad;
	}
	else if (CheckHitKey(KEY_INPUT_UP)) // ��Key
	{
		transform.rotation.x += 3.0f * DegToRad;
	}

	// �}�E�X�ʒu���擾
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	// �}�E�X�̈ړ��ʂ��擾
	int moveX = mouseX - prevMouseX;
	int moveY = mouseY - prevMouseY;
	// �J������]����i�}�E�X�j
	transform.rotation.y += moveX * 0.3f * DegToRad;
	transform.rotation.x += moveY * 0.1f * DegToRad;
	// X����](�c����)�̐���
	if (transform.rotation.x <= -20.0f * DegToRad)
	{
		transform.rotation.x = -20.0f * DegToRad;
	}
	if (transform.rotation.x >= 70.0f * DegToRad)
	{
		transform.rotation.x = 70.0f * DegToRad;
	}
	// �}�E�X�ʒu��ۑ�
	prevMouseX = mouseX;
	prevMouseY = mouseY;

	// �J�����̓v���C���[��ǂ�
	VECTOR3 camPos = lookPosition+ VECTOR3(0, 150, 0) + VECTOR3(0, 0, -427) * MGetRotX(transform.rotation.x) * MGetRotY(transform.rotation.y);
	VECTOR3 lookPos = lookPosition + VECTOR3(0, 200, 0);
	SetCameraPositionAndTarget_UpVecY(camPos, lookPos);
	#pragma endregion
}

void Camera::Draw()
{
}

void Camera::SetPlayerPosition(const VECTOR& pos)
{
	lookPosition = pos;
}
