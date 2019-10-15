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
		printStepsMade();
		Sleep(100);
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
	this->removeDeathEnds();
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
		printStepsMade();
		Sleep(100);
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
}


