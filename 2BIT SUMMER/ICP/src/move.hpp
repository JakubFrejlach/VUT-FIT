/**
 * @file 	move.hpp
 * @brief 	Class for played move
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#ifndef _MOVE_
#define _MOVE_

#include "enums.hpp"

#define UNKNOWN_POSITION -1

/**
 *	@brief Details about played move
 */
class Move
{
public:
	/**
	 *	@brief 			Sets coordinates of previous place
	 *	@param place	Square sctructure with coordinates
	 */
	void set_previous_place(Square place);

	/**
	 *	@brief 			Sets coordinates of new place
	 *	@param place	Square sctructure with coordinates
	 */
	void set_new_place(Square place);

	/**
	 *	@brief	sets mark of piece taken to true
	 */
	void set_piece_taken_mark();

	/**
	 *	@brief	sets mark of check to true
	 */
	void set_check_mark();

	/**
	 *	@brief	sets mark of checkmate to true
	 */
	void set_checkmate_mark();

	/**
	 *	@brief			sets promotion to number of figure to be promoted to
	 *	@param figure	number of figure to be promoted to
	 */
	void set_promotion(int figure);

	/**
	 *	@brief			sets piece number to actual figure
	 *	@param figure	number of figure to be set
	 */
	void set_piece(int figure);

	/**
	 *	@brief			sets number of turn
	 *	@param figure	number of turn to be set
	 */
	void set_turn_number(int turn);

	/**
	 *	@return 	Square sctructure of new place
	 */
	Square get_new_place();

	/**
	 *	@return 	Square sctructure of previous place
	 */
	Square get_previous_place();

	/**
	 *	@return 	true or false whether check is set
	 */
	bool is_check_marked();

	/**
	 *	@return 	true or false whether checkmate is set
	 */
	bool is_checkmate_marked();

	/**
	 *	@return 	true or false whether taken piece is set
	 */
	bool is_taken_piece_marked();

	/**
	 *	@return 	number of figure to be promoted to or UNKNOWN
	 */
	int is_promoted();

	/**
	 *	@return 	number of turn
	 */
	int get_turn_number();

	/**
	 *	@return 	number of piece
	 */
	int get_piece();

	/**
	 *	@return 	game id
	 */
	int get_gameId();

	/**
	 *	@brief 			function sets game id
	 *	@param gameid 	game id
	 */
	void set_gameId(int gameId);

	/**
	 *	@brief 		generates notation
	 *	@param player Player that is on turn in this move
	 */
	void generate_notation(int player);

    /**
     *	@brief  Set moveDetails converted to notation
     *	@param  string with notation
     */
    void set_notation(std::string notation);

	/**
	 *	@brief Get moveDetails converted to notation
	 *	@return Move converted to notation
	 */
	std::string get_notation();

private:
	/**
	*	@brief Previous place occupied by chess piece
	*/
	Square previousPlace;

	/**
	*	@brief New place occupied by chess piece
	*/
	Square newPlace;

	/**
	*	@brief Chess piece that did the move
	*/
	int piece;

	/**
	*	@brief Number of turn
	*/
	int turn;

	/**
	 * @brief Game Id
	 */
	int gameId;

	/**
	*	@brief Marks check in notation
	*/
	bool checkMarked = false;

	/**
	*	@brief Marks checkmate in notation
	*/
	bool checkmateMarked = false;

	/**
	*	@brief Marks piece taken in notation
	*/
	bool pieceTakenMarked = false;

	/**
	*	@brief Marks promotion in notation
	*/
 	int promotion = UNKNOWN;

	/**
	*	@brief Generated notation
	*/
 	std::string notation;
};

#endif
