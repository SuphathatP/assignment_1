#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include <iostream>
#include "game.h"

// Namespace
using namespace std;
using namespace Play;

void SpawnBall()
{
	const int objectID = CreateGameObject(TYPE_BALL, { DISPLAY_WIDTH / 2, static_cast<int>(DISPLAY_HEIGHT * topHeightDistance)}, 4, "ball");
	GameObject& ball = GetGameObject(objectID);
	ball.velocity = normalize({ -1, 1 }) * ballSpeed;
}

void StepFrame(float elapsedTime)
{
	const vector<int> brickIds = CollectGameObjectIDsByType(TYPE_BRICK);
	const vector<int> ballIds = CollectGameObjectIDsByType(TYPE_BALL);

	// Bricks collision
	for (int i = 0; i < brickIds.size(); i++)
	{
		GameObject& brick = GetGameObject(brickIds[i]);
		UpdateGameObject(brick);
		DrawObject(brick);

		for (int j = 0; j < ballIds.size(); j++)
		{
			GameObject& ball = GetGameObject(ballIds[j]);
			if (IsColliding(brick, ball))
			{
				DestroyGameObject(brickIds[i]);
				ball.velocity.y = -ball.velocity.y;
			}
		}
	}

	// Ball collision
	for (int i = 0; i < ballIds.size(); i++)
	{
		GameObject& ball = GetGameObject(ballIds[i]);
		UpdateGameObject(ball);
		DrawObject(ball);

		if (IsColliding(gPaddle, ball))
		{
			ball.velocity.y = -ball.velocity.y;


		}

		if (ball.pos.x < 0 || ball.pos.x > DISPLAY_WIDTH)
		{
			ball.velocity.x = -ball.velocity.x;
		}

		if (ball.pos.y < 0 || ball.pos.y > DISPLAY_HEIGHT)
		{
			ball.velocity.y = -ball.velocity.y;
		}
	}

	DrawPaddle(gPaddle);
	UpdatePaddle();

}

void SetupScene()
{
	// Get brick sprite size
	int brickWidth = GetSpriteWidth("brick");
	int brickHeight = GetSpriteHeight("brick");
	
	// Calculate how many colums fit the display with padding
	int brickColumns = DISPLAY_WIDTH / (brickWidth + padding);
	if (brickColumns < 1) brickColumns = 1;

	// Total grid witdth
	int totalGridWitdh = brickColumns * brickWidth + (brickColumns - 1) * padding;

	float startX = (DISPLAY_WIDTH - totalGridWitdh) / 2.0f;

	float topYDistance = 20.0f;
	float startY = static_cast<float>(DISPLAY_HEIGHT) - topYDistance - brickHeight * 0.5f;
	
	// Create bricks in a grid
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < brickColumns; ++c)
		{
			Point2f pos;
			pos.x = startX + c * (brickWidth + padding);
			pos.y = startY - r * (brickHeight + padding);

			CreateGameObject(TYPE_BRICK, pos, 6, "brick");
		}
	}
}

bool IsColliding(const Paddle& paddle, const GameObject& obj)
{
	float halfWidth = paddle.width * 0.5f;
	float halfHeight = paddle.height * 0.5f;

	Point2f bottomLeft{ paddle.pos.x - halfWidth, paddle.pos.y - halfHeight };
	Point2f topRight{ paddle.pos.x + halfWidth, paddle.pos.y + halfHeight };

	const float dx = obj.pos.x - max(bottomLeft.x, min(obj.pos.x, topRight.x));
	const float dy = obj.pos.y - max(bottomLeft.y, min(obj.pos.y, topRight.y));
	return (dx * dx + dy * dy) < (obj.radius * obj.radius);
}


