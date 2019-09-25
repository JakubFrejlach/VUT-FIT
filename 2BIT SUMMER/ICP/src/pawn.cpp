/*
 * @file 	pawn.cpp
 * @brief 	Implementations of pawn class functions
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#include <iostream>
#include <list>

#include "square.hpp"
#include "piece.hpp"
#include "enums.hpp"
#include "board_model.hpp"
#include "move.hpp"
#include "Pieces/pawn.hpp"

using namespace std;

Pawn::Pawn(Square pos, int direction) : Piece(pos)
{
	this->position = pos;
	this->moveDirection = direction;
	this->pieceType = PAWN;
}

void Pawn::move(Move moveDetail)
{
	this->position = moveDetail.get_new_place();
	this->hasMoved = true;

	// Set the flag back if we only made moves to check for checks in available moves, not real moves
	if(moveDirection == UP && this->position.row == 6)
	{
		this->hasMoved = false;
	}
	else if(moveDirection == DOWN && this->position.row == 1)
	{
		this->hasMoved = false;
	}
}

void Pawn::available_moves(BoardModel board_model)
{
	this->availableMoves.clear();
	Square pos_aux = this->position;
	int playerColor = board_model.board[pos_aux.row][pos_aux.col];
	bool canMoveByTwo = false;

	if(this->moveDirection == UP)
	{
		if(pos_aux.row > 0)
		{
			pos_aux.row += UP;

			// empty - add move
			if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
			{
				this->availableMoves.push_back(pos_aux);
				canMoveByTwo = true;
			}
		}

		if(this->hasMoved == false && canMoveByTwo == true)
		{
			pos_aux.row += UP;

			// empty - add move
			if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
			{
				this->availableMoves.push_front(pos_aux);
			}
		}

		// Check for enemies to attack
		// Up - left
		pos_aux = this->position;
		if(pos_aux.row > 0 && pos_aux.col > 0)
		{
			pos_aux.row += UP;
			pos_aux.col--;
			if(board_model.board[pos_aux.row][pos_aux.col] != playerColor && board_model.board[pos_aux.row][pos_aux.col] != PIECE_NOTHING)
			{
				this->availableMoves.push_back(pos_aux);
			}
		}

		// Up - right
		pos_aux = this->position;
		if(pos_aux.row > 0 && pos_aux.col < 7)
		{
			pos_aux.row += UP;
			pos_aux.col++;
			if(board_model.board[pos_aux.row][pos_aux.col] != playerColor && board_model.board[pos_aux.row][pos_aux.col] != PIECE_NOTHING)
			{
				this->availableMoves.push_back(pos_aux);
			}
		}
	}
	else
	{
		if(pos_aux.row < 7)
		{
			pos_aux.row += DOWN;

			// empty - add move
			if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
			{
				this->availableMoves.push_back(pos_aux);
				canMoveByTwo = true;
			}
		}

		if(this->hasMoved == false && canMoveByTwo == true)
		{
			pos_aux.row += DOWN;

			// empty - add move
			if(board_model.board[pos_aux.row][pos_aux.col] == PIECE_NOTHING)
			{
				this->availableMoves.push_back(pos_aux);
			}
		}

		// Check for enemies to attack
		// Down - left
		pos_aux = this->position;
		if(pos_aux.row < 7 && pos_aux.col > 0)
		{
			pos_aux.row += DOWN;
			pos_aux.col--;
			if(board_model.board[pos_aux.row][pos_aux.col] != playerColor && board_model.board[pos_aux.row][pos_aux.col] != PIECE_NOTHING)
			{
				this->availableMoves.push_back(pos_aux);
			}
		}

		// Down - right
		pos_aux = this->position;
		if(pos_aux.row < 7 && pos_aux.col < 7)
		{
			pos_aux.row += DOWN;
			pos_aux.col++;
			if(board_model.board[pos_aux.row][pos_aux.col] != playerColor && board_model.board[pos_aux.row][pos_aux.col] != PIECE_NOTHING)
			{
				this->availableMoves.push_back(pos_aux);
			}
		}
	}
}