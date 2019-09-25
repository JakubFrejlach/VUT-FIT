/**
 * @file 	parser.hpp
 * @brief 	Parser class
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#ifndef _PARSER_
#define _PARSER_

#include <string>
#include <list>

#include "move.hpp"

 /**
  *	@brief Starting position of lower case letters in ASCII
  */
#define ASCII_LOWER_POS 96

/**
 *	@brief Starting position of numbers from 1 in ASCII
 */
#define ASCII_NUMBER_POS 48

/**
 *	@brief Offset for converting chess numbering to array numbering
 */
#define ARRAY_NUMBERING_OFFSET -1

/**
 *	@brief Constant for swapping array counting - 0->7 to 7->0
 */
#define ARRAY_NUMBERING_FLIP 8

/**
 *	@brief Class for the notation parser
 */
class Parser
{
public:
	/**
	 *	@brief          converts string coordinates to Square sctructure
	 *  @param coord    string with coordinates
	 *	@return         Square sctructue with coordinates
	 */
	Square get_place(std::string coord);

	/**
	 *	@brief				parses chess notation from file
	 * 	@param fileName		name of file with notation to be loaded
	 * 	@param moves		pointer to list where all moves should be stored
	 *	@return				true on success or false on failure
	 */
	bool parse_notation(std::string fileName, Board *game);

	/**
	 *	@brief            converts column char to number
	 * 	@brief colChar    char representation of column
	 *	@return           number of column
	 */
	int get_col(char colChar);

	/**
	 *	@brief            converts row char to number
	 * 	@brief colChar    char representation of row
	 *	@return           number of row
	 */
	int get_row(char rowChar);

	/**
	 *	@brief            Gets number of turn from line of the notation
	 * 	@brief colChar    string representation of turn
	 *	@return           number of turn
	 */
	int get_turn_number(std::string turn);

	/**
	 *	@brief            Gets number of figure from figure name
	 * 	@brief colChar    string representation of figure name
	 *	@return           number of figure
	 */
	int get_figure_number(std::string figure);
 };

 #endif
