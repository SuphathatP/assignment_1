#include "game.h"
#include "paddle.h"

// Namespace
using namespace Play;

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	SetupScene();
	SpawnBall();

}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	ClearDrawingBuffer(cBlack);
	StepFrame(elapsedTime);
	// DrawDebugText( { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "");
	PresentDrawingBuffer();
	return KeyDown( KEY_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	DestroyManager();
	return PLAY_OK;
}
