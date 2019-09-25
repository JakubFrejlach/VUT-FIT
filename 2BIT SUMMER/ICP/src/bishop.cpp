/*
 * @file 	bishop.cpp
 * @brief 	Implementations of bishop class functions
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#include <iostream>
#include <list>

#include "square.hpp"
#include "piece.hpp"
#include "enums.hpp"
#include "board_model.hpp"
#include "move.hpp"
#include "Pieces/bishop.hpp"

using namespace std;

Bishop::Bishop(Square pos) : Piece(pos)
{
	this->position = pos;
	this->pieceType = BISHOP;
}

void Bishop::move(Move moveDetail)
{
	this->position = moveDetail.get_new_place();
}

void Bishop::available_moves(BoardModel board_model)
{
	this->availableMoves.clear();
	Square pos_aux = this->position;
	int playerColor = board_model.board[pos_aux.row][pos_aux.col];

	// Right-up
	while(pos_aux.col < 7 && pos_aux.row > 0)
	{
		pos_aux.col++;
		pos_aux.row--;

		// friendly - break
		if(board_model.board[pos_aux.row][pos_aux.col] == playerColor)
		{
			break;
		}
		// empty - check if not in check, add, continue
		else if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
		{
			this->availableMoves.push_back(pos_aux);
		}
		// enemy - check if not in check, add, break
		else
		{
			this->availableMoves.push_back(pos_aux);
			break;
		}
	}

	// Right-down
	pos_aux = this->position;
	while(pos_aux.col < 7 && pos_aux.row < 7)
	{
		pos_aux.col++;
		pos_aux.row++;

		// friendly - break
		if(board_model.board[pos_aux.row][pos_aux.col] == playerColor)
		{
			break;
		}
		// empty - check if not in check, add, continue
		else if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
		{
			this->availableMoves.push_back(pos_aux);
		}
		// enemy - check if not in check, add, break
		else
		{
			this->availableMoves.push_back(pos_aux);
			break;
		}
	}

	// Left-down
	pos_aux = this->position;
	while(pos_aux.col > 0 && pos_aux.row < 7)
	{
		pos_aux.col--;
		pos_aux.row++;

		// friendly - break
		if(board_model.board[pos_aux.row][pos_aux.col] == playerColor)
		{
			break;
		}
		// empty - check if not in check, add, continue
		else if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
		{
			this->availableMoves.push_back(pos_aux);
		}
		// enemy - check if not in check, add, break
		else
		{
			this->availableMoves.push_back(pos_aux);
			break;
		}
	}

	// Left-up
	pos_aux = this->position;
	while(pos_aux.col > 0 && pos_aux.row > 0)
	{
		pos_aux.col--;
		pos_aux.row--;

		// friendly - break
		if(board_model.board[pos_aux.row][pos_aux.col] == playerColor)
		{
			break;
		}
		// empty - check if not in check, add, continue
		else if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
		{
			this->availableMoves.push_back(pos_aux);
		}
		// enemy - check if not in check, add, break
		else
		{
			this->availableMoves.push_back(pos_aux);
			break;
		}
	}
}