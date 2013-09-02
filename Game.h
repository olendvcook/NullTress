#ifndef _Game_
#define _Game_

#pragma once

// ------ Includes -----
 
#include "Board.h"
#include "IO.h"
#include <time.h>


#endif

 
// ------ Defines -----
static int WAIT_TIME_DEFAULT = 700;
static int WAIT_TIME_AMOUNT = 700;
static int WAIT_TIME = WAIT_TIME_DEFAULT;           // Number of milliseconds that the piece remains before going 1 block down */ 
 

class Game
{
public:

	virtual ~Game(void);

	Game            (Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight);
 
    void DrawScene ();
    void CreateNewPiece ();
	void InitGame();
	void StorePiece();
 
    int mPosX, mPosY;               // Position of the piece that is falling down
    int mPiece, mRotation;          // Kind and rotation the piece that is falling down

	IO *mIO;
	Board *mBoard;


private:
 
    int mScreenHeight;              // Screen height in pixels
    int mNextPosX, mNextPosY;       // Position of the next piece
    int mNextPiece, mNextRotation;  // Kind and rotation of the next piece

	int mStoredPiece, mStoredRotation;
	int mStoredPosX, mStoredPosY;
 
    Pieces *mPieces;
 
	Game(void);
    int GetRand (int pA, int pB);
    void DrawPiece (int pX, int pY, int pPiece, int pRotation, bool isNext = false);
    void DrawBoard ();
};
