/**
 * @file 	pawn.hpp
 * @brief 	Pawn piece class
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#ifndef _PAWN_
#define _PAWN_

/**
 *	@brief Pawn piece class
 */
class Pawn : public Piece
{
public:
	/**
	 *	@brief 		Pawn class constructor
	 *	@param pos 	Initial position of piece
	 */
	Pawn(Square pos, int direction);

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

protected:
	/**
 	*	@brief Bool signalizing that pawn has moved (true forbids double move)
 	*/
	bool hasMoved = false;

	/**
 	*	@brief Direction that pawn moves in
 	*/
	int moveDirection;
};

#endif
