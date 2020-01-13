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
 		{'@',' ',' ',' ',' ',' ',' ','@',' ','@','@',' ',' ',' ','@'},
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

	   bool menu = true;
	   int p;

	   while(menu)
	   {
		   cout<<"What would you like to do?"<<endl;
		   cout<<"1.Print map"<<endl;
		   cout<<"2.Find Path"<<endl; // My algo
		   cout<<"3.Find Path, print every step"<<endl;
		   // Find Path using DFS
		   cout<<"4.Exit"<<endl;

		   Board b(worldMap);

		   cin>>p;
		   switch (p)
		   {
		   case 1:
		   {
			   b.printStepsMade();
			   break;
		   }
		   case 2:
		   {
			   b.findStartEnd(true);
			   b.findPath();
			   b.removeDeathEnds();
			   b.findStartEnd(false);

			   b.reverseFindPath();
			   b.printFinalPath();

			   b.sqr_delete();
			   b.printStepsMade();
			   break;
		   }
		   case 3:
		   {
			   b.findStartEnd(true);
			   cout<<"Empty Map"<<endl;
			   b.printStepsMade();
			   b.findPath();
			   cout<<"First walk throu map"<<endl;
			   b.printStepsMade();
			   b.removeDeathEnds();
			   cout<<"Remove of dead ends"<<endl;
			   b.printStepsMade();

			   b.findStartEnd(false);
			   b.reverseFindPath();
			   b.printFinalPath();
			   cout<<"Walk from end to begin"<<endl;
			   b.printStepsMade();

			   b.sqr_delete();
			   cout<<"Deleting squares"<<endl;
			   b.printStepsMade();
			   break;
		   }
		   case 4:
		   {
			   menu = false;
			   break;
		   }
		   }
	   }




	   return 0;
   }
