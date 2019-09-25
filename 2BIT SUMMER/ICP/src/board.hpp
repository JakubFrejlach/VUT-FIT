/**
 * @file 	board.hpp
 * @brief 	Game board class
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#ifndef _BOARD_
#define _BOARD_

#include "piece.hpp"
#include "board_model.hpp"
#include <list>

/**
 *	@brief Class for game board
 */
class Board
{
private:
	/**
	 *	@brief 8x8 game board
	 */
	Square board[8][8];

	/**
	 * 	@brief Game board model, for piece move planning (saves where enemy and friendly pieces are)
	 */
	BoardModel board_model;

	/**
	 *	@brief List of white pieces
	 */
	std::list<Piece *> whitePieces;

	/**
	 *	@brief List of black pieces
	 */
	std::list<Piece *> blackPieces;

	/**
	 *	@brief List of kicked white pieces
	 */
	std::list<Piece *> kickedWhitePieces;

	/**
	 *	@brief List of kicked black pieces
	 */
	std::list<Piece *> kickedBlackPieces;

	/**
	 *	@brief List of promoted white pawns
	 */
	std::list<Piece *> promotedWhitePawns;

	/**
	 *	@brief List of promoted black pawns
	 */
	std::list<Piece *> promotedBlackPawns;

	/**
	 *	@brief Game ID
	 */
	int gameId;

	/**
	*	@brief Color of the player that is on turn
	*/
	int onTurn = WHITE;

	/**
	*	@brief State / result of the game
	*/
	int state = IN_PROGRESS;

	/**
	*	@brief Saved replay of the match
	*/
	std::list<Move> moveHistory;

	/**
	*	@brief Number of turns made in this match
	*/
	int totalTurns = 0;

	/**
	*	@brief Error status
	*/
	int errorStatus = 0;

public:
	/**
	 *	@brief Board class constructor
	 */
	Board(int gameId);

	/**
	 * @brief Changes turn to other player
	 * @return Color of player that plays now
	 */	
	int change_player();

	/**
	 * @brief Shows who is on turn
	 * @return Color of player that plays now
	 */	
	int get_player();

	/**
	 * 	@brief Creates board model with position of all pieces on boars
	 */
	void create_board_model();

	/**
	 *	@brief Checks if one of players is in check
	 *	@return Check status based on checkStatus enum
	 */
	int is_check();

	/**
	 *	@brief Checks if one of players is in checkmate
	 *	@return Check status based on checkStatus enum
	 */
	int is_checkmate();

	/**
	 *	@brief  Checks if game ended, either by draw or checkmate
	 *	@return Game status based on gameStatus enum
	 */
	int is_end();

	/**
	 *	@brief  Performs move
	 *	@param moveDetail 	Details about performed move
	 *	@param newMove		Bool indicating whether move is new, or just redo or replay
	 *	@param player		Player on turn
	 */
	void move(Move *moveDetail, bool newMove, int player);
	

    /**
     *	@brief      Returns move history
     *  @return     all moves in game to be performed
     */
    std::list<Move> get_move_history();

	/**
	 * 	@brief Returns board model
	 *	@return Board model
	 */
	BoardModel get_board_model();

	/**
	 *	@brief Get list of white pieces
	 * 	@return List of white pieces
	 */
	std::list<Piece *> get_white_pieces();

	/**
	 *	@brief Get list of black pieces
	 * 	@return List of black pieces
	 */
	std::list<Piece *> get_black_pieces();

	/**
	 * 	@brief Kick the piece on specific square out of the game
	 *	@param place The place that kicked piece stands on
	 */
	void kick_piece(Square place);

	/**
	 * 	@brief Get all available moves of piece on given place
	 *	@param place Place that piece stands on
	 *	@return List of all possible moves
	 */
	std::list<Square> get_available_moves(Square place);

	/**
	 * 	@brief Find previous place of piece if it wasn't specified in notation
	 *	@param newPlace New place of searched piece
	 *	@return Old place of searched piece
	 */
	Square find_previous_place(Move moveDetail);

	/**
	 * 	@brief Find move with given turn number
	 *	@param turnNumber Number of turn
	 *	@return Move details
	 */
	Move* get_move(int turnNumber, int player);

	/**
	 * 	@brief Add move to list
	 *	@param moveDetail Details of new move
	 */
	void add_move(Move moveDetail);

	/**
	 * 	@brief Clears moves with bigger than given turn number (rest of replay after user played)
	 *	@param turnNumber Number of deleted turn number, anything bigger will get deleted too
	 *  @param player Current player
	 */
	void clear_moves_after_turn_number(int turnNumber, int player);

	/**
	 * @brief Get number of moves in this match
	 * @return Total number of moves
	 */
	int get_total_turns();

	/**
	 * @brief Redoes last move
	 */
	void redo(int player, int turn);

	/**
	 * @brief Undoes last move
	 */
	void undo(int player, int turn);

	/**
	 *	@brief Gets color of player that is on turn
	 * 	@return Player on turn
	 */
	int get_player_on_turn();

	/**
	 *	@brief Checks, if any of the players is able to have their pawn promoted
	 * 	@return Promotion status
	 */
	int check_promotion();

	/**
	 *	@brief Promotes pawn to different piece
	 * 	@param promoteTo Type of new piece
	 */
	void promote(int promoteTo);

	/**
	 *	@brief Get game ID
	 * 	@return Game ID
	 */
	int get_gameId() const;

	/**
	 *	@brief Get total number of moves
	 * 	@return Total number of moves
	 */
	int get_number_of_moves();

	/**
	 *	@brief Get error status
	 * 	@return 0 if good, -1 if error
	 */	
	int get_error_status();

	/**
	 *	@brief Sets error status to -1
	 */
	void set_error_status();
};

#endif