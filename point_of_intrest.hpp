/*
 * point_of_intrest.hpp
 *
 *  Created on: 20 wrz 2019
 *      Author: MJarmolkiewi
 */

#ifndef POINT_OF_INTREST_HPP_
#define POINT_OF_INTREST_HPP_
#include <iostream>
struct POI
{
	int m_X;
	int m_Y;
	POI(){};
	POI(int x, int y):m_X(x), m_Y(y){};
	void set(int x, int y)
	{
		m_X = x;
		m_Y = y;
	}
	void printPoint()
	{
		std::cout<<"X: "<<this->m_X<<" Y: "<<this->m_Y<<std::endl;
	}
	bool operator==(POI p)
	{
		if ((this->m_X == p.m_X) && (this->m_Y == p.m_Y))
		{
			return true;
		}
		return false;
	}
	POI operator=(POI p)
	{
		this->m_X = p.m_X;
		this->m_Y = p.m_Y;
		return *this;
	}
};



#endif /* POINT_OF_INTREST_HPP_ */
