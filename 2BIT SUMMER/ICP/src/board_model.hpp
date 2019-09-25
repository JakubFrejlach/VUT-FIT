/**
 * @file 	board_model.hpp
 * @brief 	Game board model class
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#ifndef _BOARDMODEL_
#define _BOARDMODEL_

enum pieces
{
	PIECE_BLACK = 0,
	PIECE_WHITE,
	PIECE_NOTHING
};

/**
 *	@brief 8x8 game board model
 */
typedef struct BoardModel
{
	int board[8][8];
} BoardModel;


#endif