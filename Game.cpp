#include "Game.h"
#include <windows.h>


Game::Game(void)
{
}

Game::Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight) 
{
	mScreenHeight = pScreenHeight;

	// Get the pointer to the Board and Pieces classes
	mBoard = pBoard;
	mPieces = pPieces;
	mIO = pIO;

	// Game initialization
	InitGame ();
}

Game::~Game(void)
{
}

/* 
======================================                                  
Get a random int between to integers
 
Parameters:
>> pA: First number
>> pB: Second number
====================================== 
*/
int Game::GetRand (int pA, int pB)
{
    return pA + (rand() % (int)(pB - pA + 1));
}

/* 
======================================                                  
Initial parameters of the game
====================================== 
*/
void Game::InitGame()
{
    // Init random numbers
    srand ((unsigned int) time(NULL));
 
    // First piece
    mPiece          = GetRand (0, 6);
    mRotation       = GetRand (0, 3);
    mPosX           = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
    mPosY           = mPieces->GetYInitialPosition (mPiece, mRotation);
 
    //  Next piece
    mNextPiece      = GetRand (0, 6);
    mNextRotation   = GetRand (0, 3);
    mNextPosX       = BOARD_WIDTH + 4;
    mNextPosY       = 3; 

	// Stored Piece
	mStoredPiece	= GetRand (0,6);
	mStoredRotation	= GetRand (0,3);
	mStoredPosX		= BOARD_WIDTH + 4;
	mStoredPosY		= 10;

	mBoard->InitBoard();
	WAIT_TIME = WAIT_TIME_DEFAULT;
	WAIT_TIME_AMOUNT = WAIT_TIME_DEFAULT;
}

/* 
======================================                                  
Create a random piece
====================================== 
*/
void Game::CreateNewPiece()
{
    // The new piece
    mPiece          = mNextPiece;
    mRotation       = mNextRotation;
    mPosX           = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
    mPosY           = mPieces->GetYInitialPosition (mPiece, mRotation);
 
    // Random next piece
    mNextPiece      = GetRand (0, 6);
    mNextRotation   = GetRand (0, 3);

}

void Game::StorePiece()
{
	int tmpPiece	= mPiece;
	int tmpRotation = mRotation;
	int tmpPosX		= mPosX;
	int tmpPosY		= mPosY;

	mPiece			= mStoredPiece;
	mRotation		= mStoredRotation;
	//will reset its pos
	mPosX           = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
    //mPosY           = mPieces->GetYInitialPosition (mPiece, mRotation);

	mStoredPiece	= tmpPiece;
	mStoredRotation	= tmpRotation;
	
}

/* 
======================================                                  
Draw piece
 
Parameters:
 
>> pX:        Horizontal position in blocks
>> pY:        Vertical position in blocks
>> pPiece:    Piece to draw
>> pRotation: 1 of the 4 possible rotations
====================================== 
*/

////////////////////////////////////////////////////////change this shit
void Game::DrawPiece (int pX, int pY, int pPiece, int pRotation, bool isNext)
{
    sf::Color mColor;               // Color of the block 
 
	switch (pPiece)
	{
		case(0):
			mColor = sf::Color::Green;
			break;
			case(1):
			mColor = sf::Color::Red;
			break;
			case(2):
			mColor = sf::Color::Yellow;
			break;
			case(3):
			mColor = sf::Color::Blue;
			break;
			case(4):
			mColor = sf::Color::Cyan;
			break;
			case(5):
				mColor = sf::Color(160,32,240);
			break;
			case(6):
				mColor = sf::Color(255,140,0);
			break;

	}
    // Obtain the position in pixel in the screen of the block we want to draw
    int mPixelsX = mBoard->GetXPosInPixels (pX);
    int mPixelsY = mBoard->GetYPosInPixels (pY);

	int fakey = pY;

	while (mBoard->IsPossibleMovement(pX,fakey+1,pPiece,pRotation))
	{
		fakey++;
	}
	int fakePixelsY = mBoard->GetYPosInPixels(fakey);
    // Travel the matrix of blocks of the piece and draw the blocks that are filled
    for (int i = 0; i < PIECE_BLOCKS; i++)
    {
        for (int j = 0; j < PIECE_BLOCKS; j++)
        {

             
            if (mPieces->GetBlockType (pPiece, pRotation, j, i) != 0)
                mIO->DrawRectangle   (mPixelsX + (i * BLOCK_SIZE), 
                                    mPixelsY + (j * BLOCK_SIZE), 
                                    BLOCK_SIZE -1, 
                                    BLOCK_SIZE -1, 
                                    mColor);
			if (isNext == false)
			{
			if (mPieces->GetBlockType (pPiece, pRotation, j, i) != 0)
                mIO->DrawRectangle   (mPixelsX + (i * BLOCK_SIZE), 
                                    fakePixelsY + (j * BLOCK_SIZE), 
                                    BLOCK_SIZE -1, 
                                    BLOCK_SIZE -1, 
                                    sf::Color::Black, true);
			}
        }
    }
}

/* 
======================================                                  
Draw board
 
Draw the two lines that delimit the board
====================================== 
*/

/////////////////////////////////////////////////change this shit
void Game::DrawBoard ()
{
	sf::Color mColor;
    // Calculate the limits of the board in pixels  
    int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
    int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);
     
    // Check that the vertical margin is not to small
    //assert (mY > MIN_VERTICAL_MARGIN);
 
    // Rectangles that delimits the board
    mIO->DrawRectangle (mX1 - BOARD_LINE_WIDTH, mY, BOARD_LINE_WIDTH, mScreenHeight - 1, sf::Color::White);
 
    mIO->DrawRectangle (mX2, mY, BOARD_LINE_WIDTH, mScreenHeight - 1, sf::Color::White);

	mIO->DrawRectangle (15, 100, 140, 230, sf::Color::Transparent, true);
	mIO->DrawRectangle (480, 100, 140, 290, sf::Color::Transparent, true);
     
    // Check that the horizontal margin is not to small
    //assert (mX1 > MIN_HORIZONTAL_MARGIN);
 
    // Drawing the blocks that are already stored in the board
    mX1 += 1;
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {   
            // Check if the block is filled, if so, draw it
            if (!mBoard->IsFreeBlock(i, j)) 
			{
				switch (mBoard->mBoard[i][j])
	{
		case(1):
			mColor = sf::Color::Green;
			break;
			case(2):
			mColor = sf::Color::Red;
			break;
			case(3):
			mColor = sf::Color::Yellow;
			break;
			case(4):
			mColor = sf::Color::Blue;
			break;
			case(5):
			mColor = sf::Color::Cyan;
			break;
			case(6):
				mColor = sf::Color(160,32,240);
			break;
			case(7):
				mColor = sf::Color(255,140,0);
			break;

	}
                mIO->DrawRectangle ( mX1 + (i * BLOCK_SIZE), 
                                        mY + (j * BLOCK_SIZE), 
                                        BLOCK_SIZE - 1, 
                                        BLOCK_SIZE - 1, 
                                        mColor);
			}

        }
    }   
}

/* 
======================================                                  
Draw scene
 
Draw all the objects of the scene
====================================== 
*/
void Game::DrawScene ()
{
    DrawBoard ();                                                   // Draw the delimitation lines and blocks stored in the board
	//DrawPiece (0, 0, mPiece, mRotation);
    DrawPiece (mPosX, mPosY, mPiece, mRotation);                    // Draw the playing piece
	DrawPiece (mStoredPosX, mStoredPosY, mStoredPiece, mStoredRotation, true);
    DrawPiece (mNextPosX, mNextPosY, mNextPiece, mNextRotation, true);    // Draw the next piece
	for(int i = 0; i < mBoard->particleEngines.size(); i++)
	{
		mBoard->particleEngines[i].Draw(&(mIO->window));
	}
	//mIO->DrawScore(mBoard->mScore);

}

