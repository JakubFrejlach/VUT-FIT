/*
 * @file    move.cpp
 * @brief   Class for played move
 * @author  Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "square.hpp"
#include "move.hpp"

using namespace std;

void Move::set_previous_place(Square place)
{
	this->previousPlace = place;
}

void Move::set_new_place(Square place)
{
	this->newPlace = place;
}

void Move::set_piece_taken_mark()
{
	this->pieceTakenMarked = true;
}

void Move::set_check_mark()
{
	this->checkMarked = true;
}

void Move::set_checkmate_mark()
{
	this->checkmateMarked = true;
}

void Move::set_promotion(int figure)
{
	this->promotion = figure;
}

void Move::set_piece(int figure)
{
	this->piece = figure;
}

void Move::set_turn_number(int turn)
{
	this->turn = turn;
}

Square Move::get_new_place()
{
	return this->newPlace;
}

Square Move::get_previous_place()
{
	return this->previousPlace;
}

bool Move::is_check_marked()
{
	return this->checkMarked;
}

bool Move::is_checkmate_marked()
{
	return this->checkmateMarked;
}

int Move::is_promoted()
{
	return this->promotion;
}

bool Move::is_taken_piece_marked()
{
	return this->pieceTakenMarked;
}

int Move::get_turn_number()
{
	return this->turn;
}

int Move::get_piece()
{
	return this->piece;
}

int Move::get_gameId()
{
	return this->gameId;
}

void Move::set_gameId(int gameId)
{
	this->gameId = gameId;
}

void Move::generate_notation(int player)
{
	this->notation.clear();

	// POSTAVIČKA - KDVJS
	if(this->piece == KNIGHT)
	{
		this->notation.push_back('J');
	}
	else if(this->piece == QUEEN)
	{
		this->notation.push_back('D');
	}
	else if(this->piece == ROOK)
	{
		this->notation.push_back('V');
	}
	else if(this->piece == BISHOP)
	{
		this->notation.push_back('S');
	}
	else if(this->piece == KING)
	{
		this->notation.push_back('K');
	}

	// POSITION FROM - a1-f8
	this->notation.push_back("abcdefgh"[this->previousPlace.col]);
	this->notation.append(std::to_string(8 - this->previousPlace.row)); // Inverts 0-7 to 1-8

	// SEBRÁNÍ - x
	if(this->is_taken_piece_marked() == true)
	{
		this->notation.push_back('x');
	}

	// POZICE KAM - a1-f8
	this->notation.push_back("abcdefgh"[this->newPlace.col]);
	this->notation.append(std::to_string(8 - this->newPlace.row)); // Inverts 0-7 to 1-8

	// VYMĚNĚNÁ POSTAVIČKA - KDVJS
	if(this->promotion != UNKNOWN)
	{
		if(this->promotion == KNIGHT)
		{
			this->notation.push_back('J');
		}
		else if(this->promotion == QUEEN)
		{
			this->notation.push_back('D');
		}
		else if(this->promotion == ROOK)
		{
			this->notation.push_back('V');
		}
		else if(this->promotion == BISHOP)
		{
			this->notation.push_back('S');
		}
		else if(this->promotion == KING)
		{
			this->notation.push_back('K');
		}
	}

	// ŠACH/MAT - +#
	if(this->is_check_marked())
	{
		this->notation.push_back('+');
	}
	else if (this->is_checkmate_marked())
	{
		this->notation.push_back('#');
	}

}

void Move::set_notation(std::string notation)
{
    this->notation.append(notation);
}

std::string Move::get_notation()
{
	return this->notation;
}
