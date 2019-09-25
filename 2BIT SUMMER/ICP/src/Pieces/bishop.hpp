/**
 * @file 	bishop.hpp
 * @brief 	Bishop piece class
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#ifndef _BISHOP_
#define _BISHOP_

/**
 *	@brief Bishop piece class
 */
class Bishop : public Piece
{
public:
	/**
	 *	@brief 		Bishop class constructor
	 *	@param pos 	Initial position of piece
	 */
	Bishop(Square pos);

	/**
	 *	@brief 	Function checks all possible moves
	 *	@return List of all available moves
	 */
	void available_moves(BoardModel board_model);

	/**
	 *	@brief Move piece to new place
	 *	@param pos New place for piece
	 */
	void move(Move moveDetail);
};

#endif
