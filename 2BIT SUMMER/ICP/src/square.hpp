/**
 * @file 	square.hpp
 * @brief 	Struct for single square on board
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#ifndef _SQUARE_
#define _SQUARE_

#include <QString>

/**
 *	@brief Single square on board
 */
typedef struct Square
{
	int row;
	int col;
    QString figure;
} Square;


#endif
