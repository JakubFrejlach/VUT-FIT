/*
 * @file 	piece.cpp
 * @brief 	Implementations of piece class functions
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#include <iostream>
#include <list>

#include "square.hpp"
#include "move.hpp"
#include "piece.hpp"

using namespace std;


Piece::Piece(Square pos)
{
	this->position = pos;
}

void Piece::available_moves(BoardModel board_model)
{
	cout << "Shouldn't be able to get here" << endl;
	cout << board_model.board[0][0] << endl;
}

std::list<Square> Piece::get_available_moves(BoardModel board_model)
{
	this->available_moves(board_model);
	return this->availableMoves;
}

int Piece::get_type() const
{
	return this->pieceType;
}

Square Piece::get_position() const
{
	return this->position;
}

void Piece::move(Move moveDetail)
{
	this->position = moveDetail.get_new_place();
}