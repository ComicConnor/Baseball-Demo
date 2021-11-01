// BaseballGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"
#include "Team.h"
#include "Player.h"
#include <iostream>
using namespace std;

int main()
{
	Player h1 = Player("Jack Trades", "JT", 50, 30, 30, "Center");
	Player h2 = Player("Lucy Field", "LF", 50, 80, 10, "Left");
	Player h3 = Player("Robert Field", "RF", 50, 10, 80, "Right");
	Player h4 = Player("Carly Field", "CF", 50, 10, 10, "Center");
	Player h5 = Player("Grant Slam", "GS", 10, 30, 30, "Right");
	Player h6 = Player("Patty Pitch", "PP", 90, 30, 30, "Left");
	Player h7 = Player("Lyle Drive", "LD", 30, 20, 40, "Center");
	Player h8 = Player("Sammy Base", "SB", 70, 60, 20, "Right");
	Player h9 = Player("Homer Runn", "HR", 20, 70, 10, "Left");

	Team homeTeam = Team("The Cracker Jacks", h1, h2, h3, h4, h5, h6, h7, h8, h9);

	Player a1 = Player("Vlad Batula", "VB", 70, 10, 10, "Center");
	Player a2 = Player("Frank Steiner", "FS", 20, 20, 70, "Left");
	Player a3 = Player("Ashley Wilhelm", "AS", 50, 10, 80, "Right");
	Player a4 = Player("Bill Visible", "BV", 70, 10, 70, "Center");
	Player a5 = Player("Brock Lagoon", "BL", 10, 50, 20, "Right");
	Player a6 = Player("Vance Helsing", "VH", 70, 30, 30, "Left");
	Player a7 = Player("Anne Carol", "AC", 50, 50, 40, "Center");
	Player a8 = Player("Hazel Salem", "HS", 70, 60, 20, "Right");
	Player a9 = Player("Wolfe Mann", "WM", 20, 70, 10, "Left");

	Team awayTeam = Team("The Ghouls", a1, a2, a3, a4, a5, a6, a7, a8, a9);
	
	string responce = "Y";
	cout << "Welcome to Oddball!!!" << endl;

	while (responce == "Y" || responce == "y" || responce == "Yes" || responce == "yes") 
	{
		int currentInning = 1;
		int totalInnings = 3;

		Game baseballGame = Game(homeTeam, awayTeam);

		cout << "Would you like to play a game (Y = Yes, N = No)?" << endl;
		cin >> responce;

		if (responce != "Y" && responce != "y" && responce != "Yes" && responce != "yes") 
		{
			break;
		}

		cout << "Your team will be " << baseballGame.getHomeTeam() << "." << endl;
		
		while (currentInning <= totalInnings) 
		{
			bool finalInning = false;

			if (currentInning == totalInnings) 
			{
				finalInning = true;
			}

			baseballGame.playInning(finalInning);
			currentInning++;
		}

		baseballGame.determineWinner();
	}
	
	cout << "Have a nice day!" << endl;
	return 0;
}




