/*
 * board.cpp
 *
 *  Created on: 20 wrz 2019
 *      Author: MJarmolkiewi
 */
#include "board.hpp"

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <vector>

Board::Board(char array[MAPSIZEX][MAPSIZEY])
{
	stepsCnt = 0;
	cnt = 0;
	for(int i = 0; i < MAPSIZEX; ++i)
	{
		for(int j = 0; j < MAPSIZEY ;++j)
		{
			mapArray[i][j] = array[i][j];
			stepsMade[i][j] = array[i][j];
		}
	}
}
void Board::cleanMap()
{
	for(int i = 0; i < MAPSIZEX; ++i)
	{
		for(int j = 0; j < MAPSIZEY ;++j)
		{
			if (stepsMade[i][j] == '&' || stepsMade[i][j] == 'B')
			{
				stepsMade[i][j] = ' ';
			}
		}
	}
}
bool Board::findStartEnd(bool flag)

{
	bool retVal1 = false;
	bool retVal2 = false;
	for(int i = 0; i < MAPSIZEX; ++i)
	{
		for(int j = 0; j < MAPSIZEY;++j)
		{
			if (mapArray[i][j] == '$')
			{
				if (flag)
				{
					m_Start.set(i,j);
					m_Boy.set(i,j);
					retVal1 = true;
				}
				else if (flag == false)
				{
					m_End.set(i,j);
					stepsMade[i][j] = '#';
					retVal2 = true;
				}
			}
			if (mapArray[i][j] == '#')
			{
				if (flag)
				{
					m_End.set(i,j);
					retVal2 = true;
				}
				else if (flag == false)
				{
					m_Start.set(i,j);
					m_Boy.set(i,j);
					stepsMade[i][j] = '$';
					retVal1 = true;
				}
			}
		}
	}
	if(retVal1 && retVal2)
	{
		return true;
	}
	return false;
}

void Board::printStepsMade()
{
	for(int i = 0; i < MAPSIZEX; ++i)
	{
		for(int j = 0; j < MAPSIZEY ;++j)
		{
			if(i == m_Boy.m_X && j == m_Boy.m_Y)
			{
				std::cout<<stepsMade[i][j];
			}
			else
			{
				std::cout<<stepsMade[i][j] ;
			}
		}
		std::cout<<std::endl;
	}
}

void Board::printMap()
{
	for(int i = 0; i < MAPSIZEX; ++i)
	{
		for(int j = 0; j < MAPSIZEY ;++j)
		{
			if(i == m_Boy.m_X && j == m_Boy.m_Y)
			{
				std::cout<<stepsMade[i][j];
			}
			else
			{
				std::cout<<mapArray[i][j] ;
			}
		}
		std::cout<<std::endl;
	}
}

void Board::printFinalPath()
{
	this->cleanMap();
	while(!boy_moves.empty())
	{
		stepsMade[boy_moves.top().m_X][boy_moves.top().m_Y] = '+';
		boy_moves.pop();
	}
	stepsMade[m_Start.m_X][m_Start.m_Y] = '$';
	stepsMade[m_End.m_X][m_End.m_Y] = '#';
}

void Board::moveUp()
{
	boy_moves.push(m_Boy);
	--m_Boy.m_X;
	stepsMade[m_Boy.m_X][m_Boy.m_Y] = '&';
}

void Board::moveDown()
{
	boy_moves.push(m_Boy);
	++m_Boy.m_X;
	stepsMade[m_Boy.m_X][m_Boy.m_Y] = '&';
}

void Board::moveRight()
{
	boy_moves.push(m_Boy);
	m_LastPoint = m_Boy;
	++m_Boy.m_Y;
	stepsMade[m_Boy.m_X][m_Boy.m_Y] = '&';
}

void Board::moveLeft()
{
	boy_moves.push(m_Boy);
	--m_Boy.m_Y;
	stepsMade[m_Boy.m_X][m_Boy.m_Y] = '&';
}

void Board::rmoveUp()
{
	boy_moves.push(m_Boy);
	--m_Boy.m_X;
	stepsMade[m_Boy.m_X][m_Boy.m_Y] = '+';
}

void Board::rmoveDown()
{
	boy_moves.push(m_Boy);
	++m_Boy.m_X;
	stepsMade[m_Boy.m_X][m_Boy.m_Y] = '+';
}

void Board::rmoveRight()
{
	boy_moves.push(m_Boy);
	m_LastPoint = m_Boy;
	++m_Boy.m_Y;
	stepsMade[m_Boy.m_X][m_Boy.m_Y] = '+';
}

void Board::rmoveLeft()
{
	boy_moves.push(m_Boy);
	--m_Boy.m_Y;
	stepsMade[m_Boy.m_X][m_Boy.m_Y] = '+';
}

void Board::removeDeathEnds()
{
	this->cleanMap();
	while(!boy_moves.empty())
	{
		stepsMade[boy_moves.top().m_X][boy_moves.top().m_Y] = '&';
		boy_moves.pop();
	}
	stepsMade[m_Start.m_X][m_Start.m_Y] = '$';
	stepsMade[m_End.m_X][m_End.m_Y] = '#';
}

bool Board::findSqrs()
{
	POI tmp;
	bool retVal = false;
	for(unsigned int i = 1; i < MAPSIZEX-1; ++i)
	{
		for(unsigned int j = 1; j < MAPSIZEY-1; ++j)
		{
			if (('+' == stepsMade[i+1][j] && '+' == stepsMade[i+1][j+1] && '+' == stepsMade[i][j+1] && '+' == stepsMade[i][j])
			 || ('+' == stepsMade[i][j+1] && '+' == stepsMade[i-1][j+1] && '+' == stepsMade[i-1][j] && '+' == stepsMade[i][j])
			 || ('+' == stepsMade[i-1][j] && '+' == stepsMade[i-1][j-1] && '+' == stepsMade[i][j-1] && '+' == stepsMade[i][j])
			 || ('+' == stepsMade[i][j-1] && '+' == stepsMade[i+1][j-1] && '+' == stepsMade[i+1][j] && '+' == stepsMade[i][j]))
			{
				tmp.set(i,j);
				sqr_fields.push_front(tmp);
				retVal = true;
			}
		}
	}
	return retVal;
}

void Board::sqr_clean(POI c1, POI c4)
{
	for(int i = c1.m_X; i < c4.m_X ; ++i)
	{
		for(int j = c1.m_Y; j < c4.m_Y; ++j)
		{
			stepsMade[i][j] = ' ';
		}
	}
	//printStepsMade();
}

void Board::sqr_FindSE()
{
	POI c1,c2,c3,c4;
	bool loop = true;

	while(!sqr_fields.empty()) //loop throu squares and find corners
	{
		c1 = sqr_fields.back(); //Top-Left Corner
		sqr_fields.pop_back();
		unsigned int y_cnt = c1.m_Y;
		unsigned int x_cnt = c1.m_X;
		POI tmp;
		while(loop) //Top Right corner
		{
			if (!('+' == stepsMade[c1.m_X+1][y_cnt] && '+' == stepsMade[c1.m_X][y_cnt]))
			{
				c2.set(c1.m_X, --y_cnt);
				loop = false;
			}
			++y_cnt;
			if (y_cnt > MAPSIZEY+1)
			{
				std::cerr<<"sqr_FindSE some shit hit the fan"<<std::endl;
				break;
			}
		}

		loop = true;
		while(loop) //Bottom Left Corner
		{
			if (!('+' == stepsMade[x_cnt][c2.m_Y] && '+' == stepsMade[x_cnt][c1.m_Y]))

			{
				c3.set(--x_cnt, c1.m_Y);
				loop = false;
			}
			++x_cnt;
			if (MAPSIZEY+1 < x_cnt)
			{
				std::cerr<<"sqr_FindSE some shit hit the fan"<<std::endl;
				break;
			}
		}
		c4.set(c3.m_X,c2.m_Y); // Bottom Right Corner

//		c1.printPoint();
//		c2.printPoint();
//		c3.printPoint();
//		c4.printPoint();

		//delete sqr from list
		for(int i = c1.m_X; i < c4.m_X ; ++i)
		{
			for(int j = c1.m_Y; j < c4.m_Y; ++j)
			{
				POI tmp;
				tmp.set(i,j);
				sqr_fields.remove(tmp);
			}
		}
		sqr_clean(c1,c4);

		//find start/end for small square
//		std::vector<POI> SE;
//		if ('+' == stepsMade[c1.m_X-1][c1.m_Y] || '+' == stepsMade[c1.m_X][c1.m_Y-1])
//		{
//			SE.push_back(c1);
//		}
//		if ('+' == stepsMade[c2.m_X-1][c2.m_Y] || '+' == stepsMade[c2.m_X][c2.m_Y+1])
//		{
//			SE.push_back(c2);
//		}
//		if ('+' == stepsMade[c3.m_X+1][c3.m_Y] || '+' == stepsMade[c3.m_X][c3.m_Y-1])
//		{
//			SE.push_back(c3);
//		}
//		if ('+' == stepsMade[c4.m_X+1][c4.m_Y] || '+' == stepsMade[c4.m_X][c4.m_Y+1])
//		{
//			SE.push_back(c4);
//		}
//		std::cout<<"Size of SE: "<<SE.size()<<std::endl;
//		SE.at(0).printPoint();
//		SE.at(1).printPoint();


//		else
//		{
//			std::cerr<<"Didnt find correct nr of corners"<<std::endl;
//		}

		//findPath();
		//printStepsMade();
	}
}
void Board::sqr_delete()
{
	bool t = true;
	while(t)
	{
		t = findSqrs();
		sqr_FindSE();
	}
}


bool Board::findPath()
{
	int xDiff = m_End.m_X - m_Start.m_X;
	int yDiff = m_End.m_Y - m_Start.m_Y;
	bool t = true;

	bool goBack = true;

	while(t)
	{
		++stepsCnt;
		xDiff = m_End.m_X - m_Boy.m_X;
		yDiff = m_End.m_Y - m_Boy.m_Y;
		goBack = true;
		if (abs(xDiff) > abs(yDiff)) // if true == move up/down
		{
			if (xDiff > 0) //preferably move to bot
			{
				if ('@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
				{
					moveDown();
					goBack = false;
				}
				else if (yDiff > 0) //preferably move to right
				{
					if('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
					{
						moveRight();
						goBack = false;
					}
					else if ('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
					{
						moveLeft();
						goBack = false;
					}
					else if (goBack && '@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move Up
					{
						moveUp();
						goBack = false;
					}
				}
				else if (yDiff <= 0) //preferably move to left
				{
					if ('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
					{
						moveLeft();
						goBack = false;
					}
					else if('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
					{
						moveRight();
						goBack = false;
					}
					else if (goBack && '@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move Up
					{
						moveUp();
						goBack = false;
					}
				}

			}
			else //preferably move to top
			{
				if ('@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move Up
				{
					moveUp();
					goBack = false;
				}
				else if (yDiff>0)
				{
					if('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
					{
						moveRight();
						goBack = false;
					}
					else if ('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
					{
						moveLeft();
						goBack = false;
					}
					else if (goBack && '@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
					{
						moveDown();
						goBack = false;
					}
				}
				else if (yDiff <= 0)
				{
					if ('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
					{
						moveLeft();
						goBack = false;
					}
					else if('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
					{
						moveRight();
						goBack = false;
					}
					else if (goBack && '@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
					{
						moveDown();
						goBack = false;
					}
				}

			}
		}
		else //move right/left
		{
			if (yDiff > 0) //preferably move to right
			{
				if('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
				{
					moveRight();
					goBack = false;
				}
				else if (xDiff > 0)
				{
					if ('@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
					{
						moveDown();
						goBack = false;
					}
					else if('@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move up
					{
						moveUp();
						goBack = false;
					}
					else if (goBack && '@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
					{
						moveLeft();
						goBack = false;
					}
				}
				else if (xDiff <= 0)
				{
					if('@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move up
					{
						moveUp();
						goBack = false;
					}
					else if ('@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
					{
						moveDown();
						goBack = false;
					}
					else if (goBack && '@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
					{
						moveLeft();
						goBack = false;
					}
				}
			}
			else //preferably move to left
			{
				if ('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
				{
					moveLeft();
					goBack = false;
				}
				else if (xDiff > 0)
				{
					if ('@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
					{
						moveDown();
						goBack = false;
					}
					else if('@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move up
					{
						moveUp();
						goBack = false;
					}
					else if(goBack && '@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
					{
						moveRight();
						goBack = false;
					}
				}
				else if (xDiff <= 0)
				{
					if('@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move up
					{
						moveUp();
						goBack = false;
					}
					else if ('@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
					{
						moveDown();
						goBack = false;
					}
					else if(goBack && '@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
					{
						moveRight();
						goBack = false;
					}
				}
			}
		}
//		printStepsMade();
//		Sleep(100);
		if (goBack)
		{
			m_Boy = boy_moves.top();
			boy_moves.pop();
		}
		if((m_Boy.m_Y == m_End.m_Y) && (m_Boy.m_X == m_End.m_X))
		{
			t = false;
		}
	}
	return true;

}

void Board::reverseFindPath()
{
	int xDiff = m_End.m_X - m_Start.m_X;
	int yDiff = m_End.m_Y - m_Start.m_Y;
	bool t = true;
	m_LastPoint.set(m_Boy.m_X,m_Boy.m_Y);
	bool goBack = true;
	this->stepsCnt = 0;
	while(t)
	{
		++stepsCnt;
		xDiff = m_End.m_X - m_Boy.m_X;
		yDiff = m_End.m_Y - m_Boy.m_Y;
		goBack = true;
		if (abs(xDiff) > abs(yDiff)) // if true == move up/down
		{
			if (xDiff > 0) //preferably move to bot
			{
				if ('@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' == stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '+' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
				{
					rmoveDown();
					goBack = false;
				}
				else if (yDiff > 0) //preferably move to right
				{
					if('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' == stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '+' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
					{
						rmoveRight();
						goBack = false;
					}
					else if ('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' == stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '+' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
					{
						rmoveLeft();
						goBack = false;
					}
					else if (goBack && '@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' == stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '+' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move Up
					{
						rmoveUp();
						goBack = false;
					}
				}
				else if (yDiff <= 0) //preferably move to left
				{
					if ('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' == stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '+' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
					{
						rmoveLeft();
						goBack = false;
					}
					else if('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' == stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '+' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
					{
						rmoveRight();
						goBack = false;
					}
					else if (goBack && '@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' == stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '+' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move Up
					{
						rmoveUp();
						goBack = false;
					}
				}
			}
			else //preferably move to top
			{
				if (goBack && '@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' == stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '+' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move Up
				{
					rmoveUp();
					goBack = false;
				}
				else if (yDiff>0)
				{
					if('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' == stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '+' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
					{
						rmoveRight();
						goBack = false;
					}
					else if ('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' == stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '+' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
					{
						rmoveLeft();
						goBack = false;
					}
					else if ('@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' == stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '+' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
					{
						rmoveDown();
						goBack = false;
					}
				}
				else if (yDiff <= 0)
				{
					if ('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' == stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '+' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
					{
						rmoveLeft();
						goBack = false;
					}
					else if('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' == stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '+' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
					{
						rmoveRight();
						goBack = false;
					}
					else if ('@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' == stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '+' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
					{
						rmoveDown();
						goBack = false;
					}
				}

			}
		}
		else //move right/left
		{
			if (yDiff > 0) //preferably move to right
			{
				if('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' == stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '+' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
				{
					rmoveRight();
					goBack = false;
				}
				else if (xDiff > 0)
				{
					if ('@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' == stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '+' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
					{
						rmoveDown();
						goBack = false;
					}
					else if (goBack && '@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' == stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '+' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move Up
					{
						rmoveUp();
						goBack = false;
					}
					else if ('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' == stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '+' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
					{
						rmoveLeft();
						goBack = false;
					}
				}
				else if (xDiff <= 0)
				{
					if (goBack && '@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' == stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '+' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move Up
					{
						rmoveUp();
						goBack = false;
					}
					else if ('@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' == stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '+' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
					{
						rmoveDown();
						goBack = false;
					}
					else if ('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' == stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '+' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
					{
						rmoveLeft();
						goBack = false;
					}
				}
			}
			else //preferably move to left
			{
				if ('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' == stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '+' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
				{
					rmoveLeft();
					goBack = false;
				}
				else if (xDiff > 0)
				{
					if ('@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' == stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '+' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
					{
						rmoveDown();
						goBack = false;
					}
					else if (goBack && '@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' == stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '+' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move Up
					{
						rmoveUp();
						goBack = false;
					}
					else if('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' == stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '+' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
					{
						rmoveRight();
						goBack = false;
					}
				}
				else if (xDiff <= 0)
				{
					if (goBack && '@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' == stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '+' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move Up
					{
						rmoveUp();
						goBack = false;
					}
					else if ('@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' == stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '+' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
					{
						rmoveDown();
						goBack = false;
					}
					else if('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' == stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '+' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
					{
						rmoveRight();
						goBack = false;
					}
				}

			}
		}
//		printStepsMade();
//		Sleep(100);
		if (goBack)
		{
			m_Boy = boy_moves.top();
			boy_moves.pop();
		}
		if(((m_Boy.m_Y+1 == m_End.m_Y) && (m_Boy.m_X == m_End.m_X))|| ((m_Boy.m_Y-1 == m_End.m_Y)&& (m_Boy.m_X == m_End.m_X))
				|| ((m_Boy.m_X+1 == m_End.m_X) && (m_Boy.m_Y == m_End.m_Y)) || ((m_Boy.m_X-1 == m_End.m_X) && (m_Boy.m_Y == m_End.m_Y)))
		{
			t = false;
		}
	}
	POI tmp = m_Start;
	m_Start = m_End;
	m_End = tmp;
}


