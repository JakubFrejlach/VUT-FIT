/*
 * @file 	chess.cpp
 * @brief 	Main file for chess program
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#include <iostream>
#include <fstream>
#include <list>
#include <regex>

#include "enums.hpp"
#include "board_model.hpp"
#include "square.hpp"
#include "board.hpp"
#include "chess.hpp"
#include "parser.hpp"

using namespace std;

void Chess::move(Move *moveDetail, bool newMove, int player)
{
	Board *game = this->get_game_by_id(moveDetail->get_gameId());
	game->move(moveDetail, newMove, player);
}

void Chess::undo(int id, int *player, int *turn)
{
	Board *game = this->get_game_by_id(id);
	if(*player == WHITE && *turn == 1)
	{
		cerr << "First turn, can't undo" << endl;
		return;
	}

	if(*player == WHITE)
	{
		*player = BLACK;
		*turn = *turn - 1;
	}
	else
	{
		*player = WHITE;
	}

	game->undo(*player, *turn);
	game->change_player();
}

void Chess::redo(int id, int *player, int *turn)
{
	Board *game = this->get_game_by_id(id);

	if(*player == game->get_player_on_turn() && *turn == game->get_total_turns())
	{
		cerr << "Last turn, can't redo" << endl;
		return;
	}

	game->redo(*player, *turn);

	if(*player == BLACK)
	{
		*player = WHITE;
		*turn = *turn + 1;
	}
	else
	{
		*player = BLACK;
	}

	game->change_player();
}

int Chess::get_total_turns(int gameId)
{
	return this->get_game_by_id(gameId)->get_total_turns();
}

Move* Chess::get_move(int gameId, int turn, int player)
{
	return this->get_game_by_id(gameId)->get_move(turn, player);
}

void Chess::replay_check_promotion(int gameId, Move *move)
{
	if(move->is_promoted() != UNKNOWN)
	{
		this->get_game_by_id(gameId)->promote(move->is_promoted());
	}
}

int Chess::change_player(int gameId)
{
	return this->get_game_by_id(gameId)->change_player();
}

int Chess::is_end(int gameId)
{
	return this->get_game_by_id(gameId)->is_end();
}

void Chess::clear_moves_after_turn_number(int gameId, int turns, int player)
{
	this->get_game_by_id(gameId)->clear_moves_after_turn_number(turns, player);
}

int Chess::check_promotion(int gameId)
{
	return this->get_game_by_id(gameId)->check_promotion();
}

void Chess::promote(int gameId, int promoteTo)
{
    this->get_game_by_id(gameId)->promote(promoteTo);
}

std::list<Move> Chess::get_history_by_gameId(int Id)
{
    return this->get_game_by_id(Id)->get_move_history();
}

bool Chess::selected_own_piece(int gameId, int player, Square selected)
{
	return this->get_game_by_id(gameId)->get_board_model().board[selected.row][selected.col] == player;
}

std::list<Square> Chess::get_available_moves(int gameId, Square place)
{
	return this->get_game_by_id(gameId)->get_available_moves(place);
}

int Chess::get_number_of_moves(int gameId)
{
	return this->get_game_by_id(gameId)->get_number_of_moves();
}

int Chess::get_error_status(int gameId)
{
	return this->get_game_by_id(gameId)->get_error_status();
}

int Chess::start()
{
	static int gameId = 0;

	this->boards.push_back(new Board(++gameId));
	return gameId;
}

Board* Chess::get_game_by_id(int id)
{
	for(const auto& i : this->boards)
	{
		if(i->get_gameId() == id)
		{
			return &*i;
		}
	}

	cerr << "Error: Didn't find game with ID: " << id << endl;
	exit(EXIT_FAILURE);
}

int Chess::get_player(int gameId)
{
	return this->get_game_by_id(gameId)->get_player();
}

bool Chess::load_game(string fileName, int gameId)
{
	Parser p;
	bool result = p.parse_notation(fileName, this->get_game_by_id(gameId));
	return result;
}