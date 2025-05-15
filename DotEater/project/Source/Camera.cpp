#include "Camera.h"
#include "../ImGui/imgui.h"
#include "Player.h"

Camera::Camera()
{
	/*rotation = VGet(80*DegToRad,0,0);
	distance = 500.0f;*/
	rotation = VGet(30 * DegToRad, 0, 0);
	distance = 300.0f;
}

Camera::~Camera()
{
}

void Camera::Update()
{

}

void Camera::Draw()
{
	Player* p = FindGameObject<Player>();
	VECTOR pRot = p->GetRotation();
	VECTOR pPos = p->GetPosition();

	VECTOR camPos = VGet(0, 200, -400) * MGetRotY(pRot.y) + pPos;
	VECTOR camLook = pPos + VGet(0, 100, 0);

	//VECTOR pos = VGet(0,0,-distance) * MGetRotX(rotation.x) * MGetRotY(rotation.y);
	SetCameraPositionAndTarget_UpVecY(camPos, camLook);
}
