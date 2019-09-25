/**
 * @file 	queen.hpp
 * @brief 	Queen piece class
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#ifndef _QUEEN_
#define _QUEEN_

/**
 *	@brief Queen piece class
 */
class Queen : public Piece
{
public:
	/**
	 *	@brief 		Queen class constructor
	 *	@param pos 	Initial position of piece
	 */
	Queen(Square pos);

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
