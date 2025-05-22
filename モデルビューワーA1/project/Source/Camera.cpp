#include "Camera.h"
#include "../ImGui/imgui.h"

Camera::Camera()
{
	rotation = VGet(0, 0, 0);
	distance = 500.0f;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		rotation.y += 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		rotation.y -= 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		rotation.x += 3.0f * DegToRad;
		if (rotation.x > 80.0f * DegToRad)
		{
			rotation.x = 80.0f * DegToRad;
		}
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		rotation.x -= 3.0f * DegToRad;
		if (rotation.x < -80.0f * DegToRad)
		{
			rotation.x = -80.0f * DegToRad;
		}
	}
	
	//char buf[20];
	//sprintf_s<20>(buf, "%f\n", rotation.x);
	//OutputDebugString(buf);

	//OutputDebugString("���݂܂���A�}���R�����Ă��炤���Ƃ��ĉ\�ł��傤��?\n");

	ImGui::Begin("rotation");
	ImGui::InputFloat("X", &rotation.x);
	ImGui::InputFloat("Y", &rotation.y);
	ImGui::InputFloat("dist", &distance);
	ImGui::End();
}

void Camera::Draw()
{
	//����ĂȂ��Ƃ� * ���
	VECTOR pos = VGet(0, 0, -distance) * MGetRotX(rotation.x) * MGetRotY(rotation.y) * MGetRotZ(rotation.z);
	SetCameraPositionAndTarget_UpVecY(pos, VGet(0, 0, 0));//(���ՁA���ՁA��O)


}
