#include "Camera.h"
#include "PadInput.h"

namespace 
{
	static float distance = 500.0f; // キャラからの距離
	static float lookHeight = 200.0f; // 注視点の高さ
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
	// →Pad
	PadInput* pad = FindGameObject<PadInput>();
	float padX = pad->RStickX();
	float padY = pad->RStickY();
	transform.rotation.y += padX * 3.0f * DegToRad;
	transform.rotation.x -= padY * 3.0f * DegToRad;

	#pragma region カメラ移動
	// 左右（キー）
	if (CheckHitKey(KEY_INPUT_RIGHT)) // →Key
	{
		transform.rotation.y += 3.0f * DegToRad;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT)) // →Key
	{
		transform.rotation.y -= 3.0f * DegToRad;
	}
	// 上下（キー）
	if (CheckHitKey(KEY_INPUT_DOWN)) // →Key
	{
		transform.rotation.x -= 3.0f * DegToRad;
	}
	else if (CheckHitKey(KEY_INPUT_UP)) // →Key
	{
		transform.rotation.x += 3.0f * DegToRad;
	}

	// マウス位置を取得
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	// マウスの移動量を取得
	int moveX = mouseX - prevMouseX;
	int moveY = mouseY - prevMouseY;
	// カメラ回転操作（マウス）
	transform.rotation.y += moveX * 0.3f * DegToRad;
	transform.rotation.x += moveY * 0.1f * DegToRad;
	// X軸回転(縦方向)の制限
	if (transform.rotation.x <= -20.0f * DegToRad)
	{
		transform.rotation.x = -20.0f * DegToRad;
	}
	if (transform.rotation.x >= 70.0f * DegToRad)
	{
		transform.rotation.x = 70.0f * DegToRad;
	}
	// マウス位置を保存
	prevMouseX = mouseX;
	prevMouseY = mouseY;

	// カメラはプレイヤーを追う
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
