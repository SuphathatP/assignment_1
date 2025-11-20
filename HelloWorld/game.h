#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include <iostream>
#include "Play.h"
#include "constants.h"
#include "paddle.h"

// Declare Functtion
void SpawnBall();
void StepFrame(float elapsedTime);
void SetupScene();
bool IsColliding(const Paddle& paddle, const Play::GameObject& obj);