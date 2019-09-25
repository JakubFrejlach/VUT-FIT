/**
 * @file 	knight.hpp
 * @brief 	Knight piece class
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#ifndef _KNIGHT_
#define _KNIGHT_

/**
 *	@brief Knight piece class
 */
class Knight : public Piece
{
public:
	/**
	 *	@brief 		Knight class constructor
	 *	@param pos 	Initial position of piece
	 */
	Knight(Square pos);

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
