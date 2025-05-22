#pragma once
#include "Object3D.h"
class PlayTime : public Object3D
{
public:
	PlayTime();
	~PlayTime();
	void Update();
	void Draw();
	/// <summary>
	/// 
	/// </summary>
	/// <returns>Time‚ª0‚É‚È‚Á‚½‚çtrue</returns>
	bool TimeUp();
private:
	float timer;
};

