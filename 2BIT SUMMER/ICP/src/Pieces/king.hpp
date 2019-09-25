/**
 * @file 	king.hpp
 * @brief 	King piece class
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#ifndef _KING_
#define _KING_

/**
 *	@brief King piece class
 */
class King : public Piece
{
public:
	/**
	 *	@brief 		King class constructor
	 *	@param pos 	Initial position of piece
	 */
	King(Square pos);

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
