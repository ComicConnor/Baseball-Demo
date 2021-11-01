#pragma once
#include "Player.h"
#include <string>

class Team {
private:
	string teamName;

	Player members[9];
	Player bench[5];
	
	Player LeftFielder;
	Player RightFielder;
	Player CenterFielder;
	Player Pitcher;

public:
	Team() 
	{
		teamName = "Boston Red Sox";
		members[0] = Player();
		members[1] = Player();
		members[2] = Player();
		members[3] = Player();
		members[4] = Player();
		members[5] = Player();
		members[6] = Player();
		members[7] = Player();
		members[8] = Player();

		bench[0] = members[0];
		bench[1] = members[1];
		bench[2] = members[2];
		bench[3] = members[3];
		bench[4] = members[4];

		LeftFielder = members[5];
		RightFielder = members[6];
		CenterFielder = members[7];
		Pitcher = members[8];
	}

	Team(string name, Player mem1, Player mem2, Player mem3, Player mem4, Player mem5, Player mem6, Player mem7, Player mem8, Player mem9) 
	{
		teamName = name;
		members[0] = mem1;
		members[1] = mem2;
		members[2] = mem3;
		members[3] = mem4;
		members[4] = mem5;
		members[5] = mem6;
		members[6] = mem7;
		members[7] = mem8;
		members[8] = mem9;

		bench[0] = members[0];
		bench[1] = members[1];
		bench[2] = members[2];
		bench[3] = members[3];
		bench[4] = members[4];

		LeftFielder = members[5];
		RightFielder = members[6];
		CenterFielder = members[7];
		Pitcher = members[8];
	}

	//Displays the team's players and their current positions.
	void viewRoster() 
	{
		cout << " " << endl;
		cout << teamName << ": " << endl;
		cout << "Bench: ";
		for (int i = 0; i <= 4; i++) 
		{
			cout << bench[i].getName() << "(" << bench[i].getInitials() << "), ";
		}
		cout << " " << endl;

		cout << "Pitcher: " << Pitcher.getName() << "(" << Pitcher.getInitials() << ")" << endl;
		cout << "Left Fielder: " << LeftFielder.getName() << "(" << LeftFielder.getInitials() << ")" << endl;
		cout << "Center Fielder: " << CenterFielder.getName() << "(" << CenterFielder.getInitials() << ")" << endl;
		cout << "Right Fielder: " << RightFielder.getName() << "(" << RightFielder.getInitials() << ")" << endl;
		cout << " " << endl;
		cout << " " << endl;
	}

	//Views the stats of an individual player on the team
	void viewStats(int playerNum) {
		if (playerNum - 1 > 0 && playerNum - 1 < 10) 
		{
			members[playerNum].checkStats();
		}
		else 
		{
			cout << "That player is not part of the team." << endl;
		}
	}

	//Views the teams line-up
	void viewLineup() {
		cout << " " << endl;
		for (int i = 0; i <= 8; i++) 
		{
			cout << members[i].getName() << "(" << members[i].getInitials() << ")" << endl;
		}
		cout << " " << endl;
	}

	//Swaps a player in the field for a player on the bench
	void swap(string position, string teamMember) 
	{
		Player onDeck;
		bool playerExists = false;
		int index = 0;
		
		for (int i = 0; i < 5; i++)
		{
			if (bench[i].getInitials() == teamMember) {
				playerExists = true;
				index = i;
				break;
			}
		}

		if(playerExists)
		{
			onDeck = bench[index];

			if (position == "l" || position == "L") 
			{
				bench[index] = LeftFielder;
				LeftFielder = onDeck;
			}
			else if (position == "r" || position == "R")
			{
				bench[index] = RightFielder;
				RightFielder = onDeck;
			}
			else if (position == "c" || position == "C")
			{
				bench[index] = CenterFielder;
				CenterFielder = onDeck;
			}
			else if (position == "p" || position == "P")
			{
				bench[index] = Pitcher;
				Pitcher = onDeck;
			}
			else 
			{
				cout << "That position does not exist." << endl;
			}
		}
		else 
		{
			cout << "That player is not on the bench." << endl;
		}
	}

	void viewPlayer(string initials) 
	{
		for (int i = 0; i < 9; i++)
		{
			if (members[i].getInitials() == initials)
			{
				members[i].checkStats();
			}
		}
	}

	//Returns a player on the team based on their initails 
	Player selectPlayer(string initials) 
	{
		for (int i = 0; i < 9; i++)
		{
			if (members[i].getInitials() == initials) 
			{
				return members[i];
			}
		}
		return members[0];
	}

	//Returns a player on the team based on their position in the members array
	Player selectPlayerFromIndex(int index)
	{
		if (0 <= index && index < 9) 
		{
			return members[index];
		}
		else 
		{
			return members[0];
		}
	}

	Player getPitcher() {
		return Pitcher;
	}

	Player getLF() {
		return LeftFielder;
	}

	Player getRF() {
		return RightFielder;
	}
	Player getCF() {
		return CenterFielder;
	}

	string getName() {
		return teamName;
	}

	bool existsBatter(string check) {
		for (int i = 0; i < 9; i++)
		{
			if (bench[i].getInitials() == check)
			{
				return true;
			}
		}

		return false;
	}
};