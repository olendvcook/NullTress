#pragma once
#ifndef _Pieces_
#define _Pieces_
#endif
class Pieces
{
public:
	Pieces(void);
	virtual ~Pieces(void);

	int GetBlockType        (int pPiece, int pRotation, int pX, int pY);
    int GetXInitialPosition (int pPiece, int pRotation);
    int GetYInitialPosition (int pPiece, int pRotation);
};

