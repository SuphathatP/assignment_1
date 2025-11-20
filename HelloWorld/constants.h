#pragma once
#include <iostream>
#include "Play.h"

// Screen
const int DISPLAY_WIDTH = 960;
const int DISPLAY_HEIGHT = 540;
const int DISPLAY_SCALE = 2;
const float topHeightDistance = 0.10f;

// Brick
const int rows = 4;
const int padding = 2;

// Ball
const float ballSpeed = 10;

// Paddle
const float paddleSpeed = 10.0f;

// Object
enum ObjectType
{
	TYPE_BALL,
	TYPE_BRICK
};