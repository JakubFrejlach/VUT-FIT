/**
 * @file 	knight.cpp
 * @brief 	Implementations of knight class functions
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#include <iostream>
#include <list>

#include "square.hpp"
#include "piece.hpp"
#include "enums.hpp"
#include "board_model.hpp"
#include "move.hpp"
#include "Pieces/knight.hpp"

using namespace std;

Knight::Knight(Square pos) : Piece(pos)
{
	this->position = pos;
	this->pieceType = KNIGHT;
}

void Knight::move(Move moveDetail)
{
	this->position = moveDetail.get_new_place();
}

void Knight::available_moves(BoardModel board_model)
{
	this->availableMoves.clear();
	Square pos_aux = this->position;
	int playerColor = board_model.board[pos_aux.row][pos_aux.col];
    
	 /**	 8 - 1
	 * 7 - - - 2
	 * - - X - - 
	 * 6 - - - 3
	 *   5 - 4
	 */

	// 1. move
	pos_aux.row -= 2;
	pos_aux.col++;
	if(pos_aux.row >= 0 && pos_aux.col <= 7)
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

	// 2. move
	pos_aux = this->position;
	pos_aux.row--;
	pos_aux.col += 2;
	if(pos_aux.row >= 0 && pos_aux.col <= 7)
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

	// 3. move
	pos_aux = this->position;
	pos_aux.row++;
	pos_aux.col += 2;
	if(pos_aux.row <= 7 && pos_aux.col <= 7)
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

	// 4. move
	pos_aux = this->position;
	pos_aux.row += 2;
	pos_aux.col++;
	if(pos_aux.row <= 7 && pos_aux.col <= 7)
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

	// 5. move
	pos_aux = this->position;
	pos_aux.row += 2;
	pos_aux.col--;
	if(pos_aux.row <= 7 && pos_aux.col >= 0)
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

	// 6. move
	pos_aux = this->position;
	pos_aux.row++;
	pos_aux.col -= 2;
	if(pos_aux.row <= 7 && pos_aux.col >= 0)
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

	// 7. move
	pos_aux = this->position;
	pos_aux.row--;
	pos_aux.col -= 2;
	if(pos_aux.row >= 0 && pos_aux.col >= 0)
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

	// 8. move
	pos_aux = this->position;
	pos_aux.row -= 2;
	pos_aux.col--;
	if(pos_aux.row >= 0 && pos_aux.col >= 0)
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