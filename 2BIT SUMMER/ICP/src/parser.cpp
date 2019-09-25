/*
 * @file     parser.cpp
 * @brief    Parser for chess notation
 * @author   Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */

#include <iostream>
#include <fstream>
#include <list>
#include <regex>
#include <string>

#include "square.hpp"
#include "board.hpp"
#include "move.hpp"
#include "enums.hpp"
#include "parser.hpp"

using namespace std;

int Parser::get_col(char colChar)
{
	return colChar - ASCII_LOWER_POS;
}

int Parser::get_row(char rowChar)
{
	return rowChar - ASCII_NUMBER_POS;
}

int Parser::get_turn_number(string turn)
{
	stringstream ss;
	int turnNumber = 0;
	for(char &c : turn)
	{
		if(isdigit(c) == false)
		{
			break;
		}
		ss << c;
	}

	ss >> turnNumber;
	return turnNumber;
}

Square Parser::get_place(string coord)
{
	Square result;
	result.row = ARRAY_NUMBERING_FLIP - this->get_row(coord.at(1));
	result.col = ARRAY_NUMBERING_OFFSET + this->get_col(coord.at(0));
	return result;
}

int Parser::get_figure_number(string figure)
{
	switch(figure.at(0))
	{
		case 'D':
			return QUEEN;
		case 'K':
			return KING;
		case 'J':
			return KNIGHT;
		case 'V':
			return ROOK;
		case 'S':
			return BISHOP;
	}

	return PAWN;
}

bool Parser::parse_notation(string fileName, Board *game)
{
	std::smatch match;                      // smatch for regex matching
	ifstream file (fileName);               // ifstream for file opening

	// Unknown place of move
	Square defaultCoord;
	defaultCoord.row = UNKNOWN_POSITION;
	defaultCoord.col = UNKNOWN_POSITION;

	// counters for turn counting
	int turnCounter = 1;
	int turnNumber = 0;

	// regexes for chess notation matching
	regex shortNotation("^[[:digit:]]+\\. [KDVSJ]?x?[a-h][1-8][KDVSJ]?[+#]?( [KDVSJ]?x?[a-h][1-8][KDVSJ]?[+#]?)?$");
	regex longNotation("^[[:digit:]]+\\. [KDVSJ]?x?[a-h][1-8][a-h][1-8][KDVSJ]?[+#]?( [KDVSJ]?x?[a-h][1-8][a-h][1-8][KDVSJP]?[+#]?)?$");
	regex coordinates("([a-h][1-8])([a-h][1-8])?");
	regex promotion("[^[:space:]]([KDVSJ])");
	regex figure("^([KDVSJ])");

	string turn;    // string to store one turn of the game

	if(file.is_open())
	{
		// parse all turns
		while(getline(file, turn))
		{
			turnNumber = this->get_turn_number(turn);

			// valid turn notation
			if((regex_match(turn, shortNotation) or regex_match(turn, longNotation)) and turnNumber == turnCounter)
			{
				// split string with turn by spaces
				istringstream buffer(turn);
				vector<string> split;
				copy(istream_iterator<string>(buffer),
					  istream_iterator<string>(),
					  back_inserter(split));

				// parse white and black moves in one turn
				for(auto s = next(split.begin()); s != split.end(); ++s)
				{
					Move m;
					m.set_turn_number(turnNumber);
                    m.set_notation(*s);

					if(regex_search(*s, match, coordinates))
					{
						// short notation
						if(match.length() == SHORT)
						{
							m.set_previous_place(defaultCoord);
							m.set_new_place(get_place(match[0]));
						}
						// long notation
						else if(match.length() == LONG)
						{
							m.set_previous_place(get_place(match[1]));
							m.set_new_place(get_place(match[2]));
						}
					}

					if(regex_search(*s, match, promotion))
					{
						m.set_promotion(get_figure_number(match[1]));
					}

					if((*s).find('x') != std::string::npos)
					{
						m.set_piece_taken_mark();
					}

					if((*s).find('#') != std::string::npos)
					{
						m.set_checkmate_mark();
					}

					if((*s).find('+') != std::string::npos)
					{
						m.set_check_mark();
					}

					if(regex_search(*s, match, figure))
					{
						m.set_piece(get_figure_number(match[1]));
					}
					else
					{
						m.set_piece(PAWN);
					}

					game->add_move(m);
				}
			}
			// invalid turn notation
			else
			{
				cerr << "ERROR: Invalid notation of the game" << endl;
				file.close();
				return false;
			}

			turnCounter++;
			turnNumber = 0;
		}
		file.close();
	}
	else
	{
		cerr << "ERROR: Cannot open file with game" << endl;
		return false;
	}
	return true;
}
