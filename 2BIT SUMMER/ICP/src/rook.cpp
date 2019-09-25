/*
 * @file 	rook.cpp
 * @brief 	Implementations of rook class functions
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#include <iostream>
#include <list>

#include "square.hpp"
#include "piece.hpp"
#include "enums.hpp"
#include "board_model.hpp"
#include "move.hpp"
#include "Pieces/rook.hpp"

using namespace std;

Rook::Rook(Square pos) : Piece(pos)
{
	this->position = pos;
	this->pieceType = ROOK;
}

void Rook::move(Move moveDetail)
{
	this->position = moveDetail.get_new_place();
}

void Rook::available_moves(BoardModel board_model)
{
	this->availableMoves.clear();
	Square pos_aux = this->position;
	int playerColor = board_model.board[pos_aux.row][pos_aux.col];
	
	// Up
	while(pos_aux.row-- > 0)
	{
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

	// Right
	pos_aux = this->position;
	while(pos_aux.col++ < 7)
	{
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

	// Down
	pos_aux = this->position;
	while(pos_aux.row++ < 7)
	{
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

	// Left
	pos_aux = this->position;
	while(pos_aux.col-- > 0)
	{
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