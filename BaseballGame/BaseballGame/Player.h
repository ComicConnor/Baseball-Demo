#pragma once
#include <string>
#include <iostream>
#include <random>
#include <time.h>
using namespace std;

class Player
{
private:
	string name;
	string initials;
	int pitchingAccuracy; //How often the player throws pitches in the strike zone.
	int battingAccuracy; //How often the player swings.
	
	int leftProficientcy; //How often the player catches the ball in left field.
	int rightProficientcy; //How often the player catches the ball in right field.
	int centerProficientcy; //How often the player catches the ball in center field.

	string hitsToField; //The field that the batter will always hit to.

	int determineProficientcy(string field)
	{
		if (field == "Left")
		{
			return leftProficientcy;
		}
		else if (field == "Right")
		{
			return rightProficientcy;
		}
		else
		{
			return centerProficientcy;
		}
	}

public:
	Player() 
	{
		name = "David";
		initials = "D";
		pitchingAccuracy = 50;
		battingAccuracy = 100 - pitchingAccuracy;

		leftProficientcy = 30;
		rightProficientcy = 30;
		centerProficientcy = 100 - (leftProficientcy + rightProficientcy);

		hitsToField = "Center";
	}

	Player(string name, string initials, int pitchingAccuracy, int leftProficientcy, int rightProficientcy, string hitsToField) 
	{
		this->name = name;
		this->initials = initials;

		this->pitchingAccuracy = pitchingAccuracy;
		battingAccuracy = 100 - pitchingAccuracy;

		this->leftProficientcy = leftProficientcy;
		this->rightProficientcy = rightProficientcy;
		centerProficientcy = 100 - (leftProficientcy + rightProficientcy);

		this->hitsToField = hitsToField;
	}

	string getName() 
	{
		return name;
	}

	string getInitials() 
	{
		return initials;
	}

	string getField() 
	{
		return hitsToField;
	}

	void setName(string newName) 
	{
		name = newName;
	}

	void setAccuracy(int newAcc) 
	{
		pitchingAccuracy = newAcc;
		battingAccuracy = 100 - pitchingAccuracy;
	}

	void checkStats() 
	{
		cout << "Name: " << name << endl;
		cout << "Pitching Accuracy: " << pitchingAccuracy << endl;
		cout << "Batting Accuracy: " << battingAccuracy << endl;
		cout << "Left Catch: " << leftProficientcy << endl;
		cout << "Right Catch: " << rightProficientcy << endl;
		cout << "Center Catch: " << centerProficientcy << endl;
		cout << "Hits to " << hitsToField << " Field." << endl;
	}

	bool swing() 
	{
		srand(time(NULL));
		int chance = rand() % 100 + 1;

		if (chance <= battingAccuracy) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	bool pitchInZone()
	{
		srand(time(NULL));
		int chance = rand() % 100 + 1;

		if (chance <= pitchingAccuracy)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool catchBall(string field)
	{
		srand(time(NULL));
		int chance = rand() % 100 + 1;
		int accuracy = determineProficientcy(field);

		if (chance <= accuracy)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};