/*
 * @file 	king.cpp
 * @brief 	Implementations of king class functions
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#include <iostream>
#include <list>

#include "square.hpp"
#include "piece.hpp"
#include "enums.hpp"
#include "board_model.hpp"
#include "move.hpp"
#include "Pieces/king.hpp"

using namespace std;

King::King(Square pos) : Piece(pos)
{
	this->position = pos;
	this->pieceType = KING;
}

void King::move(Move moveDetail)
{
	this->position = moveDetail.get_new_place();
}

void King::available_moves(BoardModel board_model)
{
	this->availableMoves.clear();
	Square pos_aux = this->position;
	int playerColor = board_model.board[pos_aux.row][pos_aux.col];

	// Upm
	if(pos_aux.row-- > 0)
	{
		// enemy - add move
		if(board_model.board[pos_aux.row][pos_aux.col] != playerColor)
		{
			this->availableMoves.push_back(pos_aux);
		}
		// empty - add move
		else if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
		{
			this->availableMoves.push_back(pos_aux);
		}
	}

	// Up-right
	pos_aux = this->position;
	if(pos_aux.row-- > 0 && pos_aux.col++ < 7)
	{	
		// enemy - add move
		if(board_model.board[pos_aux.row][pos_aux.col] != playerColor)
		{
			this->availableMoves.push_back(pos_aux);
		}
		// empty - add move
		else if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
		{
			this->availableMoves.push_back(pos_aux);
		}
	}

	// Right
	pos_aux = this->position;
	if(pos_aux.col++ < 7)
	{
		// enemy - add move
		if(board_model.board[pos_aux.row][pos_aux.col] != playerColor)
		{
			this->availableMoves.push_back(pos_aux);
		}
		// empty - add move
		else if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
		{
			this->availableMoves.push_back(pos_aux);
		}
	}

	// Right-down
	pos_aux = this->position;
	if(pos_aux.row++ < 7 && pos_aux.col++ < 7)
	{
		// enemy - add move
		if(board_model.board[pos_aux.row][pos_aux.col] != playerColor)
		{
			this->availableMoves.push_back(pos_aux);
		}
		// empty - add move
		else if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
		{
			this->availableMoves.push_back(pos_aux);
		}
	}

	// Down
	pos_aux = this->position;
	if(pos_aux.row++ < 7)
	{
		// enemy - add move
		if(board_model.board[pos_aux.row][pos_aux.col] != playerColor)
		{
			this->availableMoves.push_back(pos_aux);
		}
		// empty - add move
		else if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
		{
			this->availableMoves.push_back(pos_aux);
		}
	}

	// Down-left
	pos_aux = this->position;
	if(pos_aux.row++ < 7 && pos_aux.col-- > 0)
	{
		// enemy - add move
		if(board_model.board[pos_aux.row][pos_aux.col] != playerColor)
		{
			this->availableMoves.push_back(pos_aux);
		}
		// empty - add move
		else if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
		{
			this->availableMoves.push_back(pos_aux);
		}
	}

	// Left
	pos_aux = this->position;
	if(pos_aux.col-- > 0)
	{
		// enemy - add move
		if(board_model.board[pos_aux.row][pos_aux.col] != playerColor)
		{
			this->availableMoves.push_back(pos_aux);
		}
		// empty - add move
		else if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
		{
			this->availableMoves.push_back(pos_aux);
		}
	}

	// Left-up
	pos_aux = this->position;
	if(pos_aux.row-- > 0 && pos_aux.col-- > 0)
	{
		// enemy - add move
		if(board_model.board[pos_aux.row][pos_aux.col] != playerColor)
		{
			this->availableMoves.push_back(pos_aux);
		}
		// empty - add move
		else if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
		{
			this->availableMoves.push_back(pos_aux);
		}
	}
}