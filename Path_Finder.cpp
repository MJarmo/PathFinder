//============================================================================
// Name        : Path_Finder.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Board.hpp"
using namespace std;

   char worldMap [15][15] =
	   {{'@','@','@','@','@','@','@','@','@','@','@','@','@','@','@'},
		{'@',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@'},
		{'@',' ',' ',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ','@'},
		{'@',' ',' ',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ','@'},
		{'@',' ',' ',' ',' ',' ',' ','@',' ','@',' ',' ',' ',' ','@'},
		{'@',' ','@','@','@','@','@','@',' ','@',' ',' ',' ',' ','@'},
		{'@',' ',' ',' ',' ',' ',' ','@',' ','@','@','@',' ',' ','@'},
		{'@','@',' ',' ','@','@','@','@','@',' ','$','@',' ',' ','@'},
		{'@',' ','@',' ',' ',' ',' ','@','@',' ','@','#',' ',' ','@'},
		{'@',' ','@','@','@','@',' ','@',' ',' ','@','@',' ','@','@'},
		{'@',' ','@',' ',' ',' ',' ','@',' ',' ','@',' ',' ',' ','@'},
		{'@',' ','@',' ',' ',' ',' ','@',' ',' ','@',' ',' ',' ','@'},
		{'@',' ','@',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ','@'},
		{'@',' ',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ','@'},
		{'@','@','@','@','@','@','@','@','@','@','@','@','@','@','@'}};



int main() {
		cout<<"##############################################"<<endl;
		cout<<"############WELCOME IN PATH FINDER############"<<endl;
		cout<<"##############################################"<<endl;
		cout<<"What would you like to do?"<<endl;
		cout<<"1.Print map"<<endl;
		cout<<"2.Find Path"<<endl;
		cout<<"3.Exit"<<endl;

		Board b(worldMap);
		b.findStartEnd(true);
		b.printStepsMade();

		b.findPath();
		b.printStepsMade();
		//cout<<b.stepsCnt<<endl;

		b.findStartEnd(false);
		//cout<<b.stepsCnt<<endl;
		b.printStepsMade();

		b.reverseFindPath();
		//b.printDFSSteps();
		//cout<<b.stepsCnt<<endl;
		b.printFinalPath();
		b.printStepsMade();
		b.sqr_delete();
		b.printStepsMade();

		while(mainB)
		{
			cin>>p;
			switch (p)
			{
			case 1:
			{
				b.printMap();
				break;
			}
			case 2:
			{
				b.findStartEnd();
				b.findPath(); // my algo. Rating: 3,6/10 not great, not terrible
				break;}
			case 3:
			{

				break;
			}
			}
		}




			return 0;
}
