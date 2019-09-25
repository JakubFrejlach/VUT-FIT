/**
 * @file 	chess.hpp
 * @brief 	Game class
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#ifndef _CHESS_
#define _CHESS_

#include <list>
#include "move.hpp"
#include "board.hpp"

/**
 *	@brief Main class for the game, containing
 */
class Chess
{
public:

	/**
	 *	@brief  Performs move
	 *	@param moveDetail 	Details about performed move
	 *  @param newMove	Indicates whether move is new, or just replay or redo
	 *  @param player	Player that is on turn
	 */
	void move(Move *moveDetail, bool newMove, int player);

	/**
	 *	@brief Starts a new game
	 *	@return ID of the new game
	 */
	int start();

	/**
	 *	@brief Undo move in game with given id
	 *	@param id Id of game
	 */
	void undo(int id, int *player, int *turn);

	/**
	 *	@brief Redo move in game with given id
	 *	@param id Id of game
	 */
	void redo(int id, int *player, int *turn);

	/**
	 *	@brief Get game by ID
	 *	@param id Game ID
	 *	@return Found game
	 */
	Board* get_game_by_id(int id);
	
	/**
	 *	@brief  Loads game in chess notation and validates it
	 *	@return	returns true on success or false on failure
	 */
	bool load_game(std::string fileName, int gameId);

	/**
	 *	@brief 	Get player on turn from game
	 *	@param gameId ID of the game
	 *	@return	Player on turn
	 */
	int get_player(int gameId);

	/**
	 *	@brief 	Get total played turns of game
	 *	@param gameId ID of the game
	 *	@return	Total turns of the game
	 */
	int get_total_turns(int gameId);

	/**
	 *	@brief 	Get move details from move history
	 *	@param gameId ID of the game
	 *	@param turn Number of turn
	 * 	@param player Player on turn
	 *	@return	Details of given move
	 */
	Move* get_move(int gameId, int turn, int player);

	/**
	 *	@brief Checks and promotes piece based on replay
	 *	@param gameId ID of the game
	 * 	@param move Move details
	 */
	void replay_check_promotion(int gameId, Move *move);

	/**
	 *	@brief Changes player on turn
	 *	@param gameId ID of the game
	 * 	@return Color of current player
	 */
	int change_player(int gameId);

	/**
	 *	@brief Checks game status
	 *	@param gameId ID of the game
	 * 	@return Status of the game
	 */
	int is_end(int gameId);

	/**
	 *	@brief Clears saved moves after given turn
	 *	@param gameId ID of the game
	 * 	@param turn Turn number
	 *	@param player Player on turn
	 */
	void clear_moves_after_turn_number(int gameId, int turns, int player);

	/**
	 *	@brief Checks if player is able to have its pawn promoted
	 *	@param gameId ID of the game
	 * 	@return Promotion status
	 */
	int check_promotion(int gameId);

	/**
	 *	@brief Promotes player's pawn
	 *	@param gameId ID of the game
	 *	@param promoteTo New piece
	 */
	void promote(int gameId, int promoteTo);

    /**
     *	@brief returns move history by game Id
     *	@param Id   ID of the game
     *	@return     all moves of the game to be performed
     */
    std::list<Move> get_history_by_gameId(int Id);

    /**
     *	@brief Checks, if player selected own piece
     *	@param gameId ID of the game
     *	@param player Player color
     *	@param selected Selected square
     *	@return True if player selected own piece, false otherwise
     */
	bool selected_own_piece(int gameId, int player, Square selected);

	/**
	 *	@brief Finds all places that given piece can move to
	 *	@param gameId ID of the game
	 *	@param place Place that selected piece stands on
	 *	@return List of available moves
	 */
	std::list<Square> get_available_moves(int gameId, Square place);

	/**
	 *	@brief Get total number of moves (not turns)
	 *	@param gameId ID of the game
	 *	@return Number of moves
	 */
	int get_number_of_moves(int gameId);

	/**
	 *	@brief Get error status of given game
	 *	@param gameId ID of the game
	 *	@return 0 if no error, -1 otherwise
	 */
	int get_error_status(int gameId);
private:
	/**
 	*	@brief List of open games
 	*/
	std::list<Board *> boards;
};

#endif