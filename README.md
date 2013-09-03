NullTress
=========

Tetris Clone

Built off of base code from this tutorial:
http://javilop.com/gamedev/tetris-tutorial-in-c-platform-independent-focused-in-game-logic-for-beginners/

Controls:
	Left Right Down :: Move Left Right Down
	UP				:: Make piece drop extremely fast
	Space			:: Rotate Piece
	E				:: Store Piece
	R				:: Reset Game

Added from base:
	Switched from SDL to SFML for game libraries and drawing
	Added storing a piece feature
	Added ghosting pieces at bottom
	Added Explosion and sound when line is cleared
	Each piece is different color and color is retained when piece is stored at bottom
	Added text including number of lines cleared


TODO:
	Fix window out of focus bug.
	Refactor code to make it cleaner
	Add comments
	Pause feature
	Gamestates to add in Menu, Game over Sections
	Menu
	Game over
	Change how random numbers are generated (trolled getting same piece 5 times in a row)
	Not hardcode x and y positions of stuff so changing resulution doesnt  mess everyhting up.
	Make it work on mac and linux (it uses windows libraries)
