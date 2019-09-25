/**
 * @file 	enums.hpp
 * @brief 	Containing all needed enumerations in chess
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#ifndef _ENUMS_
#define _ENUMS_

/**
 *	@brief Enum for piece types
 */
enum pieceType
{
	KING = 0,
	QUEEN = 1,
	ROOK = 2,
	BISHOP = 3,
	KNIGHT = 4,
	PAWN = 5,
	UNKNOWN = 6
};

/**
 *	@brief Enum for pawns move directions
 */
enum moveDirection
{
	UP = -1,
	DOWN = 1
};

/**
 *	@brief Enum for piece colors
 */
enum colors
{
	BLACK = 0,
	WHITE
};

/**
 *	@brief Enum for possible states
 */
enum gameStatus
{
	IN_PROGRESS = 0,
	WHITE_WIN,
	BLACK_WIN,
	DRAW
};

/**
 *	@brief Enum for possible check states
 */
enum checkStatus
{
	NONE = 0,
	WHITE_IN_CHECK,
	BLACK_IN_CHECK,
	WHITE_IN_CHECKMATE,
	BLACK_IN_CHECKMATE
};

/**
 *	@brief Promotion status
 */
enum promotionStatus
{
	WHITE_PROMOTION = 0,
	BLACK_PROMOTION,
	NOTHING
};

/**
 *	@brief Notation types in parser
 */
enum notationParserValues
{
	SHORT = 2,
	LONG = 4
};

#endif
