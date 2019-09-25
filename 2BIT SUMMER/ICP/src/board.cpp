/*
 * @file 	board.cpp
 * @brief 	Implementations of board class functions
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#include <iostream>
#include <list>

#include "square.hpp"
#include "piece.hpp"
#include "board.hpp"
#include "enums.hpp"
#include "board_model.hpp"
#include "Pieces/king.hpp"
#include "Pieces/queen.hpp"
#include "Pieces/rook.hpp"
#include "Pieces/bishop.hpp"
#include "Pieces/knight.hpp"
#include "Pieces/pawn.hpp"

using namespace std;

void Board::move(Move *moveDetail, bool newMove, int player)
{
	// Notation did not specify previous place
	if(moveDetail->get_previous_place().col == UNKNOWN_POSITION || moveDetail->get_previous_place().row == UNKNOWN_POSITION)
	{
		moveDetail->set_previous_place(this->find_previous_place(*moveDetail));
	}

	if(player == BLACK)
	{
		for(auto& i : this->get_black_pieces())
		{
			if(i->get_position().row == moveDetail->get_previous_place().row && i->get_position().col == moveDetail->get_previous_place().col)
			{
				// Found piece, now look if we killed somebody
				for(auto const& j : this->get_white_pieces())
				{
					if(j->get_position().row == moveDetail->get_new_place().row && j->get_position().col == moveDetail->get_new_place().col)
					{
						// Kill the enemy
						this->kick_piece(moveDetail->get_new_place());
						if(newMove == true)
						{
							moveDetail->set_piece_taken_mark();
						}
						else if(moveDetail->is_taken_piece_marked() != true)
						{
							cerr << "Error: Piece capture wasn't correctly marked in notation" << endl;
							this->set_error_status();
							return;
						}
					}
				}
				
				// Move to new place
				i->move(*moveDetail);


				if(newMove == true)
				{
					moveDetail->set_piece(i->get_type());
					// Check from perspective of second player
					this->change_player();

					if(this->is_checkmate() == WHITE_IN_CHECKMATE)
					{
						moveDetail->set_checkmate_mark();
					}
					else if(this->is_check() == WHITE_IN_CHECK)
					{
						moveDetail->set_check_mark();
					}

					this->change_player();
                    this->add_move(*moveDetail);
				}
				else
				{
					// Check from perspective of second player
					this->change_player();

					if(moveDetail->is_checkmate_marked() == false && this->is_checkmate() == WHITE_IN_CHECKMATE)
					{
						cerr << "Error: Checkmate wasn't correctly marked in notation" << endl;
						this->set_error_status();
						return;
					}
					if(moveDetail->is_check_marked() == false && this->is_check() == WHITE_IN_CHECK)
					{
						cerr << "Error: Check wasn't correctly marked in notation" << endl;
						this->set_error_status();
						return;
					}

					this->change_player();
				}


				return;
			}
		}
	}
	else
	{
		// Find the piece with brute force
		for(auto& i : this->get_white_pieces())
		{
			if(i->get_position().row == moveDetail->get_previous_place().row && i->get_position().col == moveDetail->get_previous_place().col)
			{
				// Found piece, now look if we killed somebody
				for(auto const& j : this->get_black_pieces())
				{
					if(j->get_position().row == moveDetail->get_new_place().row && j->get_position().col == moveDetail->get_new_place().col)
					{
						// Kill the enemy
						this->kick_piece(moveDetail->get_new_place());
						if(newMove == true)
						{
							moveDetail->set_piece_taken_mark();
						}
						else if(moveDetail->is_taken_piece_marked() != true)
						{
							cerr << "Error: Piece capture wasn't correctly marked in notation" << endl;
							this->set_error_status();
							return;
						}
					}
				}

				// Move to new place
				i->move(*moveDetail);

				if(newMove == true)
				{
					moveDetail->set_piece(i->get_type());

					// Check from perspective of second player
					this->change_player();

					if(this->is_checkmate() == BLACK_IN_CHECKMATE)
					{
						moveDetail->set_checkmate_mark();
					}
					else if(this->is_check() == BLACK_IN_CHECK)
					{
						moveDetail->set_check_mark();
					}

					this->change_player();
                    this->add_move(*moveDetail);
				}
				else
				{
					// Check from perspective of second player
					this->change_player();

					if(moveDetail->is_checkmate_marked() == false && this->is_checkmate() == BLACK_IN_CHECKMATE)
					{
						cerr << "Error: Checkmate wasn't correctly marked in notation" << endl;
						this->set_error_status();
						return;
					}
					if(moveDetail->is_check_marked() == false && this->is_check() == BLACK_IN_CHECK)
					{
						cerr << "Error: Check wasn't correctly marked in notation" << endl;
						this->set_error_status();
						return;
					}

					this->change_player();
				}
				

				return;
			}
		}
	}

	cerr << "Error: Couldn't make move" << endl;
	this->set_error_status();
	return;
}

std::list<Move> Board::get_move_history()
{
    return this->moveHistory;
}

Board::Board(int gameId)
{
	this->gameId = gameId;

	// Initializes all squares, sets their values
	for(int rows = 0; rows < 8; rows++)
	{
		for(int cols = 0; cols < 8; cols++)
		{
			board[rows][cols].col = cols;
			board[rows][cols].row = rows;
		}
	}

	// Add all the black pieces
	this->blackPieces.push_back(new Rook(board[0][0]));
	this->blackPieces.push_back(new Knight(board[0][1]));
	this->blackPieces.push_back(new Bishop(board[0][2]));
	this->blackPieces.push_back(new Queen(board[0][3]));
	this->blackPieces.push_back(new King(board[0][4]));
	this->blackPieces.push_back(new Bishop(board[0][5]));
	this->blackPieces.push_back(new Knight(board[0][6]));
	this->blackPieces.push_back(new Rook(board[0][7]));
	this->blackPieces.push_back(new Pawn(board[1][0], DOWN));
	this->blackPieces.push_back(new Pawn(board[1][1], DOWN));
	this->blackPieces.push_back(new Pawn(board[1][2], DOWN));
	this->blackPieces.push_back(new Pawn(board[1][3], DOWN));
	this->blackPieces.push_back(new Pawn(board[1][4], DOWN));
	this->blackPieces.push_back(new Pawn(board[1][5], DOWN));
	this->blackPieces.push_back(new Pawn(board[1][6], DOWN));
	this->blackPieces.push_back(new Pawn(board[1][7], DOWN));

	// Add all the white pieces
	this->whitePieces.push_back(new Rook(board[7][0]));
	this->whitePieces.push_back(new Knight(board[7][1]));
	this->whitePieces.push_back(new Bishop(board[7][2]));
	this->whitePieces.push_back(new Queen(board[7][3]));
	this->whitePieces.push_back(new King(board[7][4]));
	this->whitePieces.push_back(new Bishop(board[7][5]));
	this->whitePieces.push_back(new Knight(board[7][6]));
	this->whitePieces.push_back(new Rook(board[7][7]));
	this->whitePieces.push_back(new Pawn(board[6][0], UP));
	this->whitePieces.push_back(new Pawn(board[6][1], UP));
	this->whitePieces.push_back(new Pawn(board[6][2], UP));
	this->whitePieces.push_back(new Pawn(board[6][3], UP));
	this->whitePieces.push_back(new Pawn(board[6][4], UP));
	this->whitePieces.push_back(new Pawn(board[6][5], UP));
	this->whitePieces.push_back(new Pawn(board[6][6], UP));
	this->whitePieces.push_back(new Pawn(board[6][7], UP));
}

void Board::create_board_model()
{
	for(int rows = 0; rows < 8; rows++)
	{
		for(int cols = 0; cols < 8; cols++)
		{
			this->board_model.board[rows][cols] = PIECE_NOTHING;

			for (auto const& i : this->whitePieces)
			{
				if(i->get_position().row == rows && i->get_position().col == cols)
				{
					this->board_model.board[rows][cols] = PIECE_WHITE;
				}
			}

			for (auto const& i : this->blackPieces)
			{
				if(i->get_position().row == rows && i->get_position().col == cols)
				{
					this->board_model.board[rows][cols] = PIECE_BLACK;
				}
			}
		}
	}
}

BoardModel Board::get_board_model()
{
	this->create_board_model();
	return this->board_model;
}

std::list<Piece *> Board::get_white_pieces()
{
	return this->whitePieces;
}

std::list<Piece *> Board::get_black_pieces()
{
	return this->blackPieces;
}

int Board::get_gameId() const
{
	return this->gameId;
}

int Board::change_player()
{
	if(this->onTurn == WHITE)
	{
		this->onTurn = BLACK;
		return this->onTurn;
	}
	else
	{
		this->onTurn = WHITE;
		return this->onTurn;
	}
}

int Board::get_player()
{
	return this->onTurn;
}

void Board::kick_piece(Square place)
{
	for(std::list<Piece *>::iterator i = this->whitePieces.begin(); i != this->whitePieces.end(); ++i)
	{
		if((*i)->get_position().row == place.row && (*i)->get_position().col == place.col)
		{
			this->kickedWhitePieces.push_back(*i);
			this->whitePieces.erase(i);
			return;
		}
	}

	for(std::list<Piece *>::iterator i = this->blackPieces.begin(); i != this->blackPieces.end(); ++i)
	{
		if((*i)->get_position().row == place.row && (*i)->get_position().col == place.col)
		{
			this->kickedBlackPieces.push_back(*i);
			this->blackPieces.erase(i);
			return;
		}
	}

	cerr << "Error: Couldn't find piece that was meant to be kicked" << endl;
	this->set_error_status();
	return;
}

int Board::is_end()
{
	int state = this->is_checkmate();

	if(state == WHITE_IN_CHECKMATE)
	{
		return BLACK_WIN;
	}
	else if(state == BLACK_IN_CHECKMATE)
	{
		return WHITE_WIN;
	}
	else if(state == WHITE_IN_CHECK || state == BLACK_IN_CHECK)
	{
		return IN_PROGRESS;
	}
	else // Check if draw
	{
		// Only both kings left
		if(this->whitePieces.size() == 1 && this->blackPieces.size() == 1)
		{
			return DRAW;
		}

		// One of the players is not in check, but can't move anywhere
		if(this->onTurn == WHITE)
		{
			for(auto const &i : this->whitePieces)
			{
				std::list<Square> available_moves = this->get_available_moves(i->get_position());
				if(available_moves.size() != 0)
				{
					return IN_PROGRESS;
				}
			}
		}
		else
		{
			for(auto const &i : this->blackPieces)
			{
				std::list<Square> available_moves = this->get_available_moves(i->get_position());
				if(available_moves.size() != 0)
				{
					return IN_PROGRESS;
				}
			}
		}
		return DRAW;
	}
}

int Board::is_checkmate()
{
	// Get game state
	this->create_board_model();
	int state = this->is_check();

	if(state == NONE)
	{
		return NONE;
	}
	else if(state == WHITE_IN_CHECK)
	{
		for(auto const &i : this->whitePieces)
		{
			std::list<Square> available_moves = this->get_available_moves(i->get_position());
			if(available_moves.size() != 0)
			{
				return WHITE_IN_CHECK;
			}
		}
		// No piece can move
		return WHITE_IN_CHECKMATE;
	}
	else
	{
		for(auto const &i : this->blackPieces)
		{
			std::list<Square> available_moves = this->get_available_moves(i->get_position());
			if(available_moves.size() != 0)
			{
				return BLACK_IN_CHECK;
			}
		}
		// No piece can move
		return BLACK_IN_CHECKMATE;
	}
}

int Board::is_check()
{
	Square whiteKing;
	Square blackKing;

	// Get position of kings
	for (auto const& i : this->whitePieces)
	{
		if(i->get_type() == KING)
		{
			whiteKing = i->get_position();
		}
	}
	for (auto const& i : this->blackPieces)
	{
		if(i->get_type() == KING)
		{
			blackKing = i->get_position();
		}
	}

	// Check if white piece can attack black king
	for (auto const& i : this->whitePieces)
	{
		// This means that there's white piece on top of square (can't kick pieces here so it basically means that it's alive)
		if(this->board_model.board[i->get_position().row][i->get_position().col] == PIECE_WHITE)
		{
			std::list<Square> available_moves = i->get_available_moves(this->board_model);
			for(auto const& j : i->availableMoves)
			{
				if(j.col == blackKing.col && j.row == blackKing.row)
				{
					return BLACK_IN_CHECK;
				}
			}
		}
	}

	// Check if black piece can attack white king
	for (auto const& i : this->blackPieces)
	{
		// This means that there's black piece on top of square (can't kick pieces here so it basically means that it's alive)
		if(this->board_model.board[i->get_position().row][i->get_position().col] == PIECE_BLACK)
		{
			std::list<Square> available_moves = i->get_available_moves(this->board_model);
			for(auto const& j : i->availableMoves)
			{
				if(j.col == whiteKing.col && j.row == whiteKing.row)
				{
					return WHITE_IN_CHECK;
				}
			}
		}
	}

	return NONE;
}

Square Board::find_previous_place(Move moveDetail)
{
	bool foundOne = false;
	Square foundPlace;
	this->create_board_model();

	Square newPlace = moveDetail.get_new_place();
	Square previousPlace = moveDetail.get_previous_place(); // If only row/col was given
	int piece = moveDetail.get_piece();


	if(this->get_player() == WHITE)
	{
		for (auto const& i : this->whitePieces)
		{
			// Previous position must match with given row/col, or be completely unknown
			if((previousPlace.row == UNKNOWN_POSITION || previousPlace.row == i->get_position().row) && (previousPlace.col == UNKNOWN_POSITION || previousPlace.col == i->get_position().col))
			{
				std::list<Square> available_moves = i->get_available_moves(this->board_model);
				for(auto const& j : available_moves)
				{
					if(j.col == newPlace.col && j.row == newPlace.row && (i->get_type() == piece || piece == UNKNOWN))
					{
						if(foundOne == true)
						{
							cerr << "Error: Can't figure out what piece should move, can choose more than one. Specify it in notation." << endl;
							this->set_error_status();
						}
						foundPlace = i->get_position();
						foundOne = true;
					}
				}
			}
		}
	}
	else
	{
		for (auto const& i : this->blackPieces)
		{
			// Previous position must match with given row/col, or be completely unknown
			if((previousPlace.row == UNKNOWN_POSITION || previousPlace.row == i->get_position().row) && (previousPlace.col == UNKNOWN_POSITION || previousPlace.col == i->get_position().col))
			{
				std::list<Square> available_moves = i->get_available_moves(this->board_model);
				for(auto const& j : available_moves)
				{
					if(j.col == newPlace.col && j.row == newPlace.row && (i->get_type() == piece || piece == UNKNOWN))
					{
						if(foundOne == true)
						{
							cerr << "Error: Can't figure out what piece should move, can choose more than one. Specify it in notation." << endl;
							this->set_error_status();
						}
						foundPlace = i->get_position();
						foundOne = true;
					}
				}
			}
		}
	}

	if(foundOne == false)
	{
		cerr << "Error: No piece can move to given position in notation." << endl;
		this->set_error_status();
	}

	return foundPlace;
}

std::list<Square> Board::get_available_moves(Square place)
{
	// List for filtered available moves
	std::list<Square> available_moves;

	// Create model, check if there's piece
	this->create_board_model();
	if(this->board_model.board[place.row][place.col] == PIECE_NOTHING)
	{
		cerr << "Error: Can't get moves - no piece on given place" << endl;
		this->set_error_status();
		return available_moves;
	}

	// Check if it's friendly piece
	if(this->board_model.board[place.row][place.col] != this->onTurn)
	{
		cerr << "Error: Can't move with enemy piece" << endl;
		this->set_error_status();
		return available_moves;
	}

	// Get the piece model
	Piece *piece;
	for(auto& i : this->whitePieces)
	{
		if(i->get_position().row == place.row && i->get_position().col == place.col)
		{
			piece = i;
		}
	}
	for(auto& i : this->blackPieces)
	{
		if(i->get_position().row == place.row && i->get_position().col == place.col)
		{
			piece = i;
		}
	}

	// Get list of available moves from piece perspective (checks and checkmates not considered)
	std::list<Square> available_moves_aux = piece->get_available_moves(this->board_model);

	// Now for every available moves check if player got into check, if yes, remove that move

	// Get player color
	int playerColor = this->board_model.board[place.row][place.col];

	for (auto& i : available_moves_aux)
	{
		// Move the piece to the available place (return later)
		Move temporary_move;
		temporary_move.set_new_place(i);
		piece->move(temporary_move);

		// Create new board model and symbolically kick enemy piece in it (only in board model, because we cant kick pieces here)
		this->create_board_model();
		this->board_model.board[i.row][i.col] = playerColor;

		if((this->is_check() == WHITE_IN_CHECK && playerColor == PIECE_WHITE) || (this->is_check() == BLACK_IN_CHECK && playerColor == PIECE_BLACK))
		{
			temporary_move.set_new_place(place);
			piece->move(temporary_move);
			continue;
		}

		// Move back
		temporary_move.set_new_place(place);
		piece->move(temporary_move);
		available_moves.push_back(i);
	}

	return available_moves;
}

int Board::get_total_turns()
{
	return this->totalTurns;
}

Move* Board::get_move(int turnNumber, int player)
{
	int currentPlayer = WHITE;
	for(auto &i : this->moveHistory)
	{
		if(i.get_turn_number() == turnNumber && player == currentPlayer)
		{
			return &i;
		}
		currentPlayer == WHITE ? currentPlayer = BLACK : currentPlayer = WHITE; // Switch player
	}

	cerr << "Error - move with this turnNumber doesn't exist" << endl;
	this->set_error_status();
	static Move empty;
	return &empty;
}

void Board::add_move(Move moveDetail)
{
	if(this->get_player_on_turn() == WHITE)
	{
		this->totalTurns++;
	}
	this->moveHistory.push_back(moveDetail);
}

void Board::clear_moves_after_turn_number(int turnNumber, int player)
{
	int currentPlayer = WHITE;
	for(std::list<Move>::iterator i = this->moveHistory.begin(); i != this->moveHistory.end();)
	{
		if(i->get_turn_number() > turnNumber || (i->get_turn_number() == turnNumber && player == currentPlayer))
		{
			this->moveHistory.erase(i++);
			continue;
		}

		i++;
		currentPlayer == WHITE ? currentPlayer = BLACK : currentPlayer = WHITE; // Switch player
	}

	this->totalTurns = turnNumber;
}

void Board::redo(int player, int turn)
{
	Move *redoMove = this->get_move(turn, player);

	this->move(redoMove, false, player);
}

void Board::undo(int player, int turn)
{
	Move *move = this->get_move(turn, player);

	// Now we need to copy values to another object so we dont overwrite our stored move
	Move undoMove;
	undoMove.set_previous_place(move->get_new_place());
	undoMove.set_new_place(move->get_previous_place());

	if(move->is_promoted() != UNKNOWN)
	{
		if(player == WHITE)
		{
			this->whitePieces.pop_back();
			this->whitePieces.push_back(this->promotedWhitePawns.back());
			this->promotedWhitePawns.pop_back();
		}
		else
		{
			this->blackPieces.pop_back();
			this->blackPieces.push_back(this->promotedBlackPawns.back());
			this->promotedBlackPawns.pop_back();
		}
	}

	if(move->is_taken_piece_marked() == true)
	{
		if(player == WHITE)
		{
			this->blackPieces.push_back(this->kickedBlackPieces.back());
			this->kickedBlackPieces.pop_back();
		}
		else
		{
			this->whitePieces.push_back(this->kickedWhitePieces.back());
			this->kickedWhitePieces.pop_back();
		}
	}

	this->move(&undoMove, false, player);
}

int Board::get_player_on_turn()
{
	if((this->moveHistory.size() % 2) == 0)
	{
		return WHITE;
	}
	return BLACK;
}

int Board::check_promotion()
{
	for (auto const& i : this->whitePieces)
	{
		if(i->get_position().row == 0 && i->get_type() == PAWN)
		{
			return WHITE_PROMOTION;
		}
	}

	for (auto const& i : this->blackPieces)
	{
		if(i->get_position().row == 7 && i->get_type() == PAWN)
		{
			return BLACK_PROMOTION;
		}
	}

	return NOTHING;
}

void Board::promote(int promoteTo)
{
	// Find the promoted piece
	for(std::list<Piece *>::iterator i = this->whitePieces.begin(); i != this->whitePieces.end(); ++i)
	{
		if((*i)->get_position().row == 0 && (*i)->get_type() == PAWN)
		{
			Square pos = (*i)->get_position();

			this->promotedWhitePawns.push_back(*i);
			this->whitePieces.erase(i);

			if(promoteTo == QUEEN)
			{
				this->whitePieces.push_back(new Queen(board[pos.row][pos.col]));
			}
			else if(promoteTo == BISHOP)
			{
				this->whitePieces.push_back(new Bishop(board[pos.row][pos.col]));
			}
			else if(promoteTo == ROOK)
			{
				this->whitePieces.push_back(new Rook(board[pos.row][pos.col]));
			}
			else if(promoteTo == KNIGHT)
			{
				this->whitePieces.push_back(new Knight(board[pos.row][pos.col]));
			}
			else
			{
				cerr << "Error: Can't promote piece" << endl;
				this->set_error_status();
				return;
			}
			return;
		}
	}

	for(std::list<Piece *>::iterator i = this->blackPieces.begin(); i != this->blackPieces.end(); ++i)
	{
		if((*i)->get_position().row == 7 && (*i)->get_type() == PAWN)
		{
			Square pos = (*i)->get_position();

			this->promotedBlackPawns.push_back(*i);
			this->blackPieces.erase(i);

			if(promoteTo == QUEEN)
			{
				this->blackPieces.push_back(new Queen(board[pos.row][pos.col]));
			}
			else if(promoteTo == BISHOP)
			{
				this->blackPieces.push_back(new Bishop(board[pos.row][pos.col]));
			}
			else if(promoteTo == ROOK)
			{
				this->blackPieces.push_back(new Rook(board[pos.row][pos.col]));
			}
			else if(promoteTo == KNIGHT)
			{
				this->blackPieces.push_back(new Knight(board[pos.row][pos.col]));
			}
			else
			{
				cerr << "Error: Can't promote piece" << endl;
				this->set_error_status();
				return;
			}
			return;
		}
	}
}

int Board::get_number_of_moves()
{
	return this->moveHistory.size();
}

int Board::get_error_status()
{
	return this->errorStatus;
}

void Board::set_error_status()
{
	this->errorStatus = -1;
}
