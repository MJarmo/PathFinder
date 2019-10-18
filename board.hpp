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
#include <list>
class Board
{
public:
	//Board
	POI m_Start;
	POI m_End;
	POI m_Boy;
	POI m_LastPoint;
	//My Algo
	char mapArray[MAPSIZEX][MAPSIZEY];
    char stepsMade[MAPSIZEX][MAPSIZEY];
    int stepsCnt;
    std::stack<POI> boy_moves;

	//Optymalization Path
	int cnt;
	std::list<POI> sqr_fields;
	bool findSqrs();
	void sqr_FindSE();
	void sqr_clean(POI c1, POI c4);
	void sqr_delete();
	void rmoveUp();
	void rmoveDown();
	void rmoveRight();
	void rmoveLeft();
	void printFinalPath();
	Board(char array[MAPSIZEX][MAPSIZEY]);
	bool findStartEnd(bool flag);
	void printMap();
	void printStepsMade();
	bool findPath();
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void removeDeathEnds();
	void cleanMap();
	void reverseFindPath();
};



#endif /* BOARD_HPP_ */
