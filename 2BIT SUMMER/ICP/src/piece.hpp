/**
 * @file 	piece.hpp
 * @brief 	Piece class
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#ifndef _PIECE_
#define _PIECE_

#include "move.hpp"
#include "board_model.hpp"

/**
 *	@brief Parent class for all piece types
 */
class Piece
{
public:
	/**
	 *	@brief 	Function checks all possible moves
	 *	@return List of all available moves
	 *	@param board_model Model of board
	 */
	virtual void available_moves(BoardModel board_model);

	/**
	 *	@brief 	Function gets all possible moves
	 *	@return List of all available moves
	 */
	std::list<Square> get_available_moves(BoardModel board_model);

	/**
	 *	@brief 		Piece class constructor
	 *	@param pos 	Initial position of piece
	 */
	Piece(Square pos);

	/**
	 *  @brief  Get type of piece
	 *  @return Type of the piece
	 */
	int get_type() const;

	/**
	 *  @brief  Get position of piece
	 *  @return Position of piece
	 */
	Square get_position() const;

	/**
	 *	@brief Move piece to new place
	 *	@param pos New place for piece
	 */
	virtual void move(Move moveDetail);
	/**
	 *	@brief Available moves of piece
	 */
	std::list<Square> availableMoves;
protected:
	/**
	 *	@brief Position of the piece
	 */
	Square position;


	/**
	 *  @brief Type of the piece
	 */
	int pieceType;
};

#endif
