/*
 * Board.hpp
 *
 *  Created on: 20 wrz 2019
 *      Author: MJarmolkiewi
 */

#ifndef BOARD_HPP_
#define BOARD_HPP_

#define MAPSIZEX 15u
#define MAPSIZEY 15u
#include "point_of_intrest.hpp"
#include <stack>
class Board
{
public:
	POI m_Start;
	POI m_End;
	POI m_Boy;
	POI m_LastPoint;
	char mapArray[MAPSIZEX][MAPSIZEY];
    char stepsMade[MAPSIZEX][MAPSIZEY];
    int stepsCnt;

    std::stack<POI> boy_moves;
	Board(char array[MAPSIZEX][MAPSIZEY]);
	bool findStartEnd();
	void printMap();
	bool findPath();
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
;
};



#endif /* BOARD_HPP_ */
