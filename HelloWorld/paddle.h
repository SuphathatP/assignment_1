#pragma once
#include <iostream>
#include "Play.h"
#include "constants.h"

struct Paddle
{
	Play::Point2f pos{ 0.0f, 0.0f };

	int width{ 100 };
	int height{ 16 };

	Play::Colour defaultColor = { 100, 100, 100 }; // Default color (Cyan)
	Play::Colour color{ 100, 100, 100 };        // Paddle color
	int colorFrames{ 0 };

};

extern Paddle gPaddle;

void DrawPaddle(const Paddle& paddle);
void UpdatePaddle();