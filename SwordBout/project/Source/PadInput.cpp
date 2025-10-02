#include "PadInput.h"
#include <assert.h>

PadInput::PadInput(int id) 
{


	padId = id;
	DontDestroyOnSceneChange();
}

PadInput::~PadInput() 
{
}

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
}

float PadInput::LStickX()
{
	if (input.ThumbLX >= ZERO_RANGE) 
	{
		float ret = (float)(input.ThumbLX - ZERO_RANGE) / (MAX - ZERO_RANGE);
		// +１を上回ってしまった場合(念のため)
		if (ret > 1.0f) 
		{
			ret = 1.0f;
		}
		return ret;
	}
	else
	{
		if (input.ThumbLX <= -ZERO_RANGE) 
		{
			float ret = (float)(input.ThumbLX + ZERO_RANGE) / (MAX - ZERO_RANGE);
			// -１を下回ってえてしまった場合(念のため)
			if (ret < -1.0f)
			{
				ret = -1.0f;
			}
			return ret;
		}
	}
	return 0.0f;
}

float PadInput::LStickY()
{
	if (input.ThumbLY >= ZERO_RANGE)
	{
		float ret = (float)(input.ThumbLY - ZERO_RANGE) / (MAX - ZERO_RANGE);
		// +１を上回ってしまった場合(念のため)
		if (ret > 1.0f)
		{
			ret = 1.0f;
		}
		return ret;
	}
	else
	{
		if (input.ThumbLY <= -ZERO_RANGE)
		{
			float ret = (float)(input.ThumbLY + ZERO_RANGE) / (MAX - ZERO_RANGE);
			// -１を下回ってえてしまった場合(念のため)
			if (ret < -1.0f)
			{
				ret = -1.0f;
			}
			return ret;
		}
	}
	return 0.0f;
}

float PadInput::RStickX()
{
	if (input.ThumbRX >= ZERO_RANGE)
	{
		float ret = (float)(input.ThumbRX - ZERO_RANGE) / (MAX - ZERO_RANGE);
		// +１を上回ってしまった場合(念のため)
		if (ret > 1.0f)
		{
			ret = 1.0f;
		}
		return ret;
	}
	else
	{
		if (input.ThumbRX <= -ZERO_RANGE)
		{
			float ret = (float)(input.ThumbRX + ZERO_RANGE) / (MAX - ZERO_RANGE);
			// -１を下回ってえてしまった場合(念のため)
			if (ret < -1.0f)
			{
				ret = -1.0f;
			}
			return ret;
		}
	}
}

float PadInput::RStickY()
{
	if (input.ThumbRY >= ZERO_RANGE)
	{
		float ret = (float)(input.ThumbRY - ZERO_RANGE) / (MAX - ZERO_RANGE);
		// +１を上回ってしまった場合(念のため)
		if (ret > 1.0f)
		{
			ret = 1.0f;
		}
		return ret;
	}
	else
	{
		if (input.ThumbRY <= -ZERO_RANGE)
		{
			float ret = (float)(input.ThumbRY + ZERO_RANGE) / (MAX - ZERO_RANGE);
			// -１を下回ってえてしまった場合(念のため)
			if (ret < -1.0f)
			{
				ret = -1.0f;
			}
			return ret;
		}
	}
	return 0.0f;
}

VECTOR2 PadInput::LStickVec()
{
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
}

VECTOR2 PadInput::RStickVec()
{
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
}

bool PadInput::Press(int id)
{
	assert(id < 16); //?
	return input.Buttons[id] > 0;
}

bool PadInput::OnPush(int id)
{
	assert(id < 16); //?
	return input.Buttons[id] > 0 && prevButtons[id] == 0;
}

void PadInput::Reset()
{
}
