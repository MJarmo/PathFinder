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
			optimalizationMap[i][j] = array[i][j];
		}
	}
}

bool Board::findStartEnd()
{
	bool retVal1 = false;
	bool retVal2 = false;
	for(int i = 0; i < MAPSIZEX; ++i)
	{
		for(int j = 0; j < MAPSIZEY;++j)
		{
			if (mapArray[i][j] == '$')
			{
				m_Start.set(i,j);
				m_Boy.set(i,j);
				retVal1 = true;
			}
			if (mapArray[i][j] == '#')
			{
				m_End.set(i,j);
				retVal2 = true;
			}
		}
	}
	if(retVal1 && retVal2)
	{
		return true;
	}
	return false;
}
void Board::printMap()
{
	for(int i = 0; i < MAPSIZEX; ++i)
	{
		for(int j = 0; j < MAPSIZEY ;++j)
		{
			if(i == m_Boy.m_X && j == m_Boy.m_Y)
			{
				std::cout<<"B";
			}
			else
			{
				std::cout<<mapArray[i][j] ;
			}
		}
		std::cout<<std::endl;
	}
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
void Board::checkForDeadEnds()
{
	while(!boy_moves.empty())
	{
		optimalizationMap[boy_moves.top().m_X][boy_moves.top().m_Y] = '+';
		boy_moves.pop();
	}
	optimalizationMap[m_Start.m_X][m_Start.m_Y] = '$';

	for(int i = 0; i < MAPSIZEX; ++i)
	{
		for(int j = 0; j < MAPSIZEY ;++j)
		{
			if(i == m_Boy.m_X && j == m_Boy.m_Y)
			{
				std::cout<<"B";
			}
			else
			{
				std::cout<<optimalizationMap[i][j];
			}
		}
		std::cout<<std::endl;
	}
}
void Board::optymizePath(POI p)
{
	++cnt;
	current = p;
}
bool Board::findPath()
{
	int xDiff = m_End.m_X - m_Start.m_X;
	int yDiff = m_End.m_Y - m_Start.m_Y;
	bool t = true;
	m_LastPoint.set(m_Boy.m_X,m_Boy.m_Y);
	bool goBack = true;

	while(t)
	{
		++stepsCnt;
		xDiff = m_End.m_X - m_Boy.m_X;
		yDiff = m_End.m_Y - m_Boy.m_Y;
		goBack = true;
		if (abs(xDiff) > abs(yDiff)) // if true == move up/down
		{
			if (xDiff > 0) //preferably move from from top to bot
			{
				if ('@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
				{
					moveDown();
					goBack = false;
				}
				else if (yDiff > 0) //preferably move from left to right
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
				}
				else if (yDiff <= 0) //preferably move from right to left
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
				}
				if (goBack && '@' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X-1][m_Boy.m_Y]) // move Up
				{
					moveUp();
					goBack = false;
				}
			}
			else //preferably move from bottom to top
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
				}
				else if ('@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
				{
					moveLeft();
					goBack = false;
				}
				if (goBack && '@' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '&' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y] && '$' != stepsMade[m_Boy.m_X+1][m_Boy.m_Y]) // move Down
				{
					moveDown();
					goBack = false;
				}
			}
		}
		else //move right/left
		{
			if (yDiff > 0) //preferably move from left to right
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
				}
				if (goBack && '@' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y-1]) // move Left
				{
					moveLeft();
					goBack = false;
				}


			}
			else //preferably move from right to left
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
				}
				if(goBack && '@' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '&' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1] && '$' != stepsMade[m_Boy.m_X][m_Boy.m_Y+1]) //move Right
				{
					moveRight();
					goBack = false;
				}
			}
		}
		std::cout <<"xDiff:" << xDiff<< " yDiff:"<<yDiff<<std::endl;
		printMap();
		//Sleep(200);
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

void Board::printStepsMade()
{
	for(int i = 0; i < MAPSIZEX; ++i)
	{
		for(int j = 0; j < MAPSIZEY ;++j)
		{
			if(i == m_Boy.m_X && j == m_Boy.m_Y)
			{
				std::cout<<"B";
			}
			else
			{
				std::cout<<stepsMade[i][j] ;
			}
		}
		std::cout<<std::endl;
	}
}
