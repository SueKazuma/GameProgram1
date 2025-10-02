#include "PadInput.h"
#include <assert.h>
#define USE_MOUSE_CAMERA // ƒ}ƒEƒX‚Å‰EƒXƒeƒBƒbƒN‚Ì•Ï‚í‚è
#define USE_KEYBOARD_MOVE // ƒL[ƒ{[ƒh‚ÅˆÚ“®

static const int MAX = 32767;
static const int LIMIT = MAX / 5;

PadInput::PadInput(int id)
{
    pad_id = id;
    DontDestroyOnSceneChange();
#ifdef USE_MOUSE_CAMERA // ƒ}ƒEƒX‚Å‰EƒXƒeƒBƒbƒN‚Ì•Ï‚í‚è
    GetMousePoint(&prevMouseX, &prevMouseY);
#endif
}

PadInput::~PadInput()
{
}

<<<<<<< HEAD
float StickValue(int stick) {
    if (-LIMIT < stick && stick < LIMIT)
    {
        return 0.0f;
    } else if (stick > 0)
    {
        float ret = (float)(stick - LIMIT) / (MAX - LIMIT);
        if (ret > 1.0f) {
            ret = 1.0f;
        }
        return ret;
    } else
    {
        float ret = (float)(stick + LIMIT) / (MAX - LIMIT);
        if (ret < -1.0f) {
            ret = -1.0f;
        }
        return ret;
    }
=======
void PadInput::Update()
{
	for (int i = 0; i < 16; i++)
	{
		prevButtons[i] = input.Buttons[i];
	}
	GetJoypadXInputState(padId, &input);
	if (CheckHitKey(KEY_INPUT_M)) 
	{
		input.Buttons[XINPUT_BUTTON_A] = 1;
	}
}

void PadInput::Draw()
{
	DrawFormatString(200, 50, GetColor(255, 255, 255), "LStick %d %d", input.ThumbLX, input.ThumbLY);
>>>>>>> ä¸Šæ›¸ãå‰ï¼Ÿ
}

float PadInput::LStickX()
{
    return StickValue(input.ThumbLX);
}

float PadInput::LStickY()
{
    return StickValue(input.ThumbLY);
}

float PadInput::RStickX()
{
    return StickValue(input.ThumbRX);
}

float PadInput::RStickY()
{
    return StickValue(input.ThumbRY);
}

VECTOR2 StickVec(int x, int y)
{
    float size = sqrtf((float)x*x + (float)y*y);
    if (size < LIMIT)
    {
        return VECTOR2(0, 0);
    }
    else if (size > MAX)
    {
        return VECTOR2(x / size, y / size);
    }
    else
    {
        return VECTOR2(x / (float)MAX, y / (float)MAX);
    }
}

VECTOR2 PadInput::LStickVec()
{
<<<<<<< HEAD
    VECTOR2 ret = VECTOR2(LStickX(), LStickY());
    if (CheckHitKey(KEY_INPUT_W)) 
    {
        ret += VECTOR2(0, 1);
    }
    if (CheckHitKey(KEY_INPUT_S)) 
    {
        ret += VECTOR2(0, -1);
    }
    if (CheckHitKey(KEY_INPUT_D)) 
    {
        ret += VECTOR2(1, 0);
    }
    if (CheckHitKey(KEY_INPUT_A)) 
    {
        ret += VECTOR2(-1, 0);
    }
    if (ret.Size() > 1.0f) 
    {
        ret = ret.Normalize();
    }
    return ret;
=======
	VECTOR2 ret = VECTOR2(LStickX(), LStickY());
	if (CheckHitKey(KEY_INPUT_W)) // Key
	{
		ret += VECTOR2(0, 1);
	}
	if (CheckHitKey(KEY_INPUT_S)) // Key
	{
		ret += VECTOR2(0, -1);
	}
	if (CheckHitKey(KEY_INPUT_D)) // Key
	{
		ret += VECTOR2(1, 0);
	}
	if (CheckHitKey(KEY_INPUT_A)) // Key
	{
		ret += VECTOR2(-1, 0);
	}
	if (ret.Size() > 1.0f) 
	{
		ret = ret.Normalize();
	}
	return ret;
>>>>>>> ä¸Šæ›¸ãå‰ï¼Ÿ
}

VECTOR2 PadInput::RStickVec()
{
<<<<<<< HEAD
    return StickVec(input.ThumbRX, input.ThumbRY);
=======
	VECTOR2 ret = VECTOR2(RStickX(), RStickY());
	if (CheckHitKey(KEY_INPUT_W)) // Key
	{
		ret += VECTOR2(0, 1);
	}
	if (CheckHitKey(KEY_INPUT_S)) // Key
	{
		ret += VECTOR2(0, -1);
	}
	if (CheckHitKey(KEY_INPUT_D)) // Key
	{
		ret += VECTOR2(1, 0);
	}
	if (CheckHitKey(KEY_INPUT_A)) // Key
	{
		ret += VECTOR2(-1, 0);
	}
	if (ret.Size() > 1.0f)
	{
		ret = ret.Normalize();
	}
	return ret;
>>>>>>> ä¸Šæ›¸ãå‰ï¼Ÿ
}

bool PadInput::Press(int id)
{
    assert(id < 16);
    return input.Buttons[id] > 0;
}

bool PadInput::OnPush(int id)
{
<<<<<<< HEAD
    assert(id < 16);
    return input.Buttons[id] > 0 && prevButtons[id] == 0;
=======
	assert(id < 16); //?
	return input.Buttons[id] > 0 && prevButtons[id] == 0;
>>>>>>> ä¸Šæ›¸ãå‰ï¼Ÿ
}

void PadInput::Reset()
{
    GetMousePoint(&prevMouseX, &prevMouseY);
    for (int i = 0; i < 16; i++)
    {
        prevButtons[i] = 1;
    }
}

inline int clamp(int v, int minV, int maxV)
{
    if (v < minV)
        return minV;
    if (v > maxV)
        return maxV;
    return v;
}

void PadInput::Update()
{

    for (int i = 0; i < 16; i++)
    {
        prevButtons[i] = input.Buttons[i];
    }
    GetJoypadXInputState(pad_id, &input);



#ifdef USE_KEYBOARD_MOVE
    if (CheckHitKey(KEY_INPUT_W))
    {
        input.ThumbLY = -MAX;
    }
    if (CheckHitKey(KEY_INPUT_S))
    {
        input.ThumbLY = MAX;
    }
    if (CheckHitKey(KEY_INPUT_D))
    {
        input.ThumbLX = MAX;
    }
    if (CheckHitKey(KEY_INPUT_A))
    {
        input.ThumbLX = -MAX;
    }
#endif
#ifdef USE_MOUSE_CAMERA
    static const int SENSE = 40;
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    int dragX = (mouseX - prevMouseX) * MAX / SENSE;
    int dragY = (mouseY - prevMouseY) * MAX / SENSE;
    input.ThumbRX = clamp(dragX + input.ThumbRX, -MAX, MAX);
    input.ThumbRY = clamp(dragY + input.ThumbRY, -MAX, MAX);
    prevMouseX = mouseX;
    prevMouseY = mouseY;
#endif
    if (GetMouseInput() & MOUSE_INPUT_LEFT)
    {
        input.Buttons[XINPUT_BUTTON_X] = 1;
    }
}
