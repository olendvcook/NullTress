
#include "Game.h"
#include <SFML\Graphics.hpp>
#include <SFML/System.hpp>
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	IO mIO;

	int mScreenHeight = mIO.HEIGHT;

	// Pieces
	Pieces mPieces;

	// Board
	Board mBoard (&mPieces, mScreenHeight);

	// Game
	Game mGame (&mBoard, &mPieces, &mIO, mScreenHeight);

	sf::Clock clock;
	// Get the actual clock milliseconds (SDL)
	sf::Time mTime1 = clock.getElapsedTime();

	mIO.window.setKeyRepeatEnabled(false);
	sf::Event event;

	sf::Font font;
	font.loadFromFile("font.ttf");

	sf::Text text("LINES CLEARED:", font);
	sf::Text tScore;
	//text.setString("Number of Lines Cleared:");
	text.setPosition(20,110);
	text.setColor(sf::Color::White);
	text.setCharacterSize(14);

	tScore.setPosition(70,130);
	tScore.setFont(font);
	tScore.setColor(sf::Color::Cyan);
	tScore.setCharacterSize(30);

	sf::Text tInstructions;
	tInstructions.setString("\n ROTATE: SPACE \n\n STORE:	E \n\n PLACE:	UP \n\n RESET:	R \n\n QUIT:	 ESC");
	tInstructions.setPosition(15,180);
	tInstructions.setFont(font);
	tInstructions.setColor(sf::Color::White);
	tInstructions.setCharacterSize(14);

	sf::Text tNext("NEXT:", font);
	tNext.setPosition(525,120);
	tNext.setColor(sf::Color::White);
	tNext.setCharacterSize(16);

	sf::Text tStored("STORED:", font);
	tStored.setPosition(515,270);
	tStored.setColor(sf::Color::White);
	tStored.setCharacterSize(16);
		
	int lastScore = 0;

	while (1)
	{
		if((mBoard.mScore - lastScore) == 10)
		{
			lastScore = mBoard.mScore;
			if (WAIT_TIME_AMOUNT > 200) WAIT_TIME_AMOUNT -= 100;
			WAIT_TIME = WAIT_TIME_AMOUNT;
		}
		for(int i = 0; i < mGame.mBoard->particleEngines.size(); i++)
		{
			mGame.mBoard->particleEngines[i].Update(0.1, true);
		}
		mIO.ClearScreen (); 		// Clear screen
		mGame.DrawScene ();			// Draw stuff
		std::string s = std::to_string(mBoard.mScore);
		tScore.setString(s);
		mIO.window.draw(text);
		mIO.window.draw(tScore);
		mIO.window.draw(tInstructions);
		mIO.window.draw(tNext);
		mIO.window.draw(tStored);
		mIO.UpdateScreen ();		// Put the graphic context in the screen


		int mKey = mIO.Pollkey();

		switch (mKey)
		{
		case (sf::Keyboard::Right): 
			{
				if (mBoard.IsPossibleMovement (mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					mGame.mPosX++;
				break;
			}

		case (sf::Keyboard::Left): 
			{
				if (mBoard.IsPossibleMovement (mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					mGame.mPosX--;	
				break;
			}

		case (sf::Keyboard::Down):
			{
				if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
					mGame.mPosY++;	
				break;
			}

		case (sf::Keyboard::Up):
			{
				WAIT_TIME = 15;
				/*
				// Check collision from up to down
				while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) { mGame.mPosY++; }

				mBoard.StorePiece (mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);

				mBoard.DeletePossibleLines ();

				if (mBoard.IsGameOver())
				{
					mIO.Getkey();
					mBoard.InitBoard();
					//exit(0);
				}

				mGame.CreateNewPiece();
				 */
				break;
				
			}

		case (sf::Keyboard::Space):
			{
				if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
					mGame.mRotation = (mGame.mRotation + 1) % 4;

				break;
			}
		case (sf::Keyboard::Escape):
			{
				exit(0);
				break;
			}
		case (sf::Keyboard::R):
			{
				WAIT_TIME_AMOUNT = WAIT_TIME_DEFAULT;
				WAIT_TIME = WAIT_TIME_DEFAULT;
				lastScore = 0;
				mGame.InitGame();
			}

		case (sf::Keyboard::E):
			{
				mGame.StorePiece();
			}
		}



		// ----- Vertical movement -----

		sf::Time mTime2 = clock.getElapsedTime();

		if ((mTime2.asMilliseconds() - mTime1.asMilliseconds()) > WAIT_TIME)
		{
			if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
			{
				mGame.mPosY++;
			}
			else
			{
				mBoard.StorePiece (mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
				WAIT_TIME = WAIT_TIME_AMOUNT;

				mBoard.DeletePossibleLines ();

				if (mBoard.IsGameOver())
				{
					mIO.Getkey();
					WAIT_TIME = WAIT_TIME_DEFAULT;
					WAIT_TIME_AMOUNT = WAIT_TIME_DEFAULT;
					lastScore = 0;
					mGame.InitGame();
					//exit(0);
				}

				mGame.CreateNewPiece();
			}

			mTime1 = clock.getElapsedTime();
		}

	}

	return 0;
}

void particlesUpdate()
{

}