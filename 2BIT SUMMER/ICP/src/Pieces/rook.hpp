/**
 * @file 	rook.hpp
 * @brief 	Rook piece class
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#ifndef _ROOK_
#define _ROOK_

/**
 *	@brief Rook piece class
 */
class Rook : public Piece
{
public:
	/**
	 *	@brief 		Rook class constructor
	 *	@param pos 	Initial position of piece
	 */
	Rook(Square pos);

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
