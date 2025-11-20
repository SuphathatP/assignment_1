#include <iostream>
#include "paddle.h"

using namespace std;
using namespace Play;

Paddle gPaddle;

void DrawPaddle(const Paddle& paddle)
{
	float halfWidth = paddle.width * 0.5f;
	float halfHeight = paddle.height * 0.5f;

	Point2f bottomLeft{ paddle.pos.x - halfWidth, paddle.pos.y - halfHeight };
	Point2f topRight{ paddle.pos.x + halfWidth, paddle.pos.y + halfHeight };

	DrawRect(bottomLeft, topRight, paddle.color, true);
}

void UpdatePaddle()
{
	// Move left
	if (KeyDown(KEY_A) || KeyDown(KEY_LEFT))
	{
		gPaddle.pos.x -= paddleSpeed;
	}

	// Move right
	if (KeyDown(KEY_D) || KeyDown(KEY_RIGHT))
	{
		gPaddle.pos.x += paddleSpeed;
	}

	// Clamp paddle to screen size
	const float halfWidth = gPaddle.width * 0.5;
	gPaddle.pos.x = clamp(gPaddle.pos.x, halfWidth, static_cast<float>(DISPLAY_WIDTH) - halfWidth);

	// Handle temporary hit-colour timer (frames)
	if (gPaddle.colorFrames > 0)
	{
		--gPaddle.colorFrames;
		
		if (gPaddle.colorFrames == 0)
		{
			gPaddle.color = gPaddle.defaultColor;
		}
	}
}