#pragma once
#include "Player.h"
#include "Team.h"
#include <string>
#include <vector>

class Game {
private:
	Team homeTeam;
	int homeScore;

	Team awayTeam;
	int awayScore;

	bool onFirst = false;
	bool onSecond = false;
	bool onThird = false;

	//Simulates when the player's team is batting.
	void atBat() {
		int strikes = 0;
		int balls = 0;
		int outs = 0;
		vector<string>discard;

		while (outs < 3) 
		{
			string choice = "a";
			int action = 0;
			string playerIni = "a";
			bool selectionMade = false;
			Player pitcher = awayTeam.getPitcher();
			Player batter;

			//Player picks an action to perform
			cout << "Select an action (S = Select Batter, R = View Roster, P = View Player)." << endl;
			cin >> choice;
			action = determineChoice(choice);

			switch (action) 
			{
			case 1: //Select Batter: The user picks a batter from their line-up
				playerIni = chooseBatter(discard);
				batter = homeTeam.selectPlayer(playerIni);
				discard.push_back(playerIni);
				selectionMade = true;
				break;

			case 2: //View Roster: Checks the roster of either the home or away team
				teamRoster();
				break;

			case 3: //View Player: Checks the stats of an individual player on either the home or away team
				checkPlayer();
				break;

			default:
				cout << "That action does not exist." << endl;
				choice = "a";
				break;
			}

			while (selectionMade && strikes < 3 && balls < 4) //Once the player has selected a batter...
			{
				srand(time(NULL));
				if (pitcher.pitchInZone() && batter.swing()) //If the pitch is in the strike zone and the batter swings
				{
					cout << "Ball is hit!" << endl;
					Player fielder = determineFielder(batter.getField(), awayTeam);

					if (fielder.catchBall(batter.getField()) == false) //Hit sucessful if the fielder fails to make the catch
					{
						cout << "Sucessful hit!" << endl;
						int chance = rand() % 4 + 1;

						hitBall(homeScore, chance);
						strikes = 0;
						break;
					}
					else //Batter out if the ball is caught
					{
						cout << "Ball caught, batter out." << endl;
						outs++;
						strikes = 0;
						break;
					}
				}
				//If the batter does not swing while the ball is in the strike zone or if the batter swings while the ball is out of the strike zone.
				else if ((pitcher.pitchInZone() == false && batter.swing()) || (pitcher.pitchInZone() && batter.swing() == false)) 
				{
					cout << "Strike!" << endl;
					strikes++;
				}
				//If the ball is out of the strike zone and the batter does not swing.
				else 
				{
					cout << "Ball!" << endl;
					balls++;
				}
			}

			if (strikes >= 3) //Batter out after three stikes
			{
				cout << "Batter out!" << endl;
				outs++;
			}

			if (balls >= 4) //Batter walked after four balls
			{
				cout << "Batter walked!" << endl;
				hitBall(homeScore, 1);
			}

			//Count resets.
			strikes = 0;
			balls = 0;
			if (discard.size() == 9) 
			{
				discard.clear();
			}
		}
	}

	void onField() 
	{
		int outs = 0;
		int index = 0;

		while (outs < 3) 
		{
			string choice = "a";
			int action = 0;
			string playerIni;
			string position;
			bool continueOn = false;
			Player pitcher;
			Player batter;
			int strikes = 0;
			int balls = 0;

			//Player picks an action to perform
			cout << "Select an action (S = Swap Positions, R = View Roster, P = View Player, C = Continue)." << endl;
			cin >> choice;
			action = determineChoice(choice);
			
			switch (action)
			{
			case 1: //Swap Positions: The user swaps out one player for a player on the bench
				homeTeam.viewRoster();

				cout << "Enter the initials of the benched player you want to swap with." << endl;
				cin >> playerIni;

				cout << "Enter the position you want them in (P = Pitcher, L = Left Fielder, R = Right Fielder, C = Center Fielder)." << endl;
				cin >> position;

				homeTeam.swap(position, playerIni);
				break;

			case 2: //View Roster: Checks the roster of either the home or away team
				teamRoster();
				break;

			case 3: //View Player: Checks the stats of an individual player on either the home or away team
				checkPlayer();
				break;

			default: //Continue: Proceeds to the on field events
				continueOn = true;
				break;
			}

			pitcher = homeTeam.getPitcher();
			batter = awayTeam.selectPlayerFromIndex(index);
			index++;
			
			if (index >= 8) 
			{
				index = 0;
			}
			
			while (continueOn && strikes < 3 && balls < 4)
			{
				srand(time(NULL));
				cout << "Now batting: " << batter.getName() << endl;

				if (pitcher.pitchInZone() && batter.swing()) //If the pitch is in the strike zone and the batter swings
				{
					cout << "Ball is hit!" << endl;
					Player fielder = determineFielder(batter.getField(), homeTeam);

					if (fielder.catchBall(batter.getField()) == false) //Hit sucessful if the fielder fails to make the catch
					{
						cout << "Sucessful hit!" << endl;
						int chance = rand() % 4 + 1;

						hitBall(awayScore, chance);
						strikes = 0;
						break;
					}
					else //Batter out if the ball is caught
					{
						cout << "Ball caught, batter out." << endl;
						outs++;
						strikes = 0;
						break;
					}
				}
				//If the batter does not swing while the ball is in the strike zone or if the batter swings while the ball is out of the strike zone.
				else if ((pitcher.pitchInZone() == false && batter.swing()) || (pitcher.pitchInZone() && batter.swing() == false))
				{
					cout << "Strike!" << endl;
					strikes++;
				}
				//If the ball is out of the strike zone and the batter does not swing.
				else
				{
					cout << "Ball!" << endl;
					balls++;
				}
			}
			
			if (strikes >= 3) //Batter out after three strikes
			{
				cout << "Batter out!" << endl;
				outs++;
			}

			if (balls >= 4) //Batter out after four balls
			{
				cout << "Batter walked!" << endl;
				hitBall(awayScore, 1);
			}

			//Count resets
			strikes = 0;
			balls = 0;
			continueOn = false;
		}
	}

	//Accessed in at bat. Allows the user to choose a player from their lineup to bat.
	string chooseBatter(vector<string>&illegal) {
		cout << "Your Lineup:" << endl;
		homeTeam.viewLineup();

		cout << " " << endl;
		cout << "Discard: " << endl;

		if (illegal.empty() == false) 
		{
			for (int i = 0; i <= illegal.size() - 1; i++)
			{
				cout << illegal[i] << ", ";
			}
		}
		
		cout << " " << endl;

		string choice = "a";
		bool playerChose = false;

		while (playerChose == false) 
		{
			cout << "Select the player by their initials." << endl;
			cin >> choice;

			if (homeTeam.existsBatter(choice))
			{
				bool match = false;
				if (illegal.empty() == false) 
				{
					for (int i = 0; i <= illegal.size() - 1; i++)
					{
						if (illegal[i] == choice)
						{
							match = true;
							break;
						}
					}
				}
				
				if (match) 
				{
					cout << "That player has been chosen." << endl;
				}
				else
				{
					playerChose = true;
				}
			}
			else 
			{
				cout << "That player is not on your team." << endl;
			}
		}
		
		return choice;
	}

	//Accesses ViewPlayer in the teams class based on a team picked by the user
	void teamRoster()
	{
		string team;
		Team check;
		bool exists = false;

		cout << "Which team would you like to check (Type Home or Away)?" << endl;
		cin >> team;

		if (team == "home" || team == "Home")
		{
			check = homeTeam;
			exists = true;
		}
		else if (team == "away" || team == "Away")
		{
			check = awayTeam;
			exists = true;
		}
		else
		{
			cout << "That team does not exist." << endl;
		}

		if (exists) {
			check.viewRoster();
		}
	}

	//Accesses ViewPlayer in the teams class based on user specifications
	void checkPlayer() {
		string team;
		Team check;
		string playerIni = "a";
		bool exists = false;

		//Choose home or away team
		cout << "Which team would you like to check (Type Home or Away)?" << endl;
		cin >> team;

		if (team == "home" || team == "Home")
		{
			check = homeTeam;
			exists = true;
		}
		else if (team == "away" || team == "Away")
		{
			check = awayTeam;
			exists = true;
		}
		else
		{
			cout << "That team does not exist." << endl;
		}

		//Choose the player based on their initials
		if (exists) {
			check.viewLineup();
			cout << "Enter the initials of the player you want to check." << endl;
			cin >> playerIni;

			if (check.existsBatter(playerIni))
			{
				check.viewPlayer(playerIni);
			}
			else 
			{
				cout << "That player is not on the team." << endl;
			}
		}
	}

	//Determines who is trying to catch a hit ball based on the batters prefered field
	Player determineFielder(string field, Team fieldingTeam) 
	{
		Player fielder;

		if (field == "Left") 
		{
			fielder = fieldingTeam.getLF();
		}
		else if (field == "Right")
		{
			fielder = fieldingTeam.getRF();
		}
		else if (field == "Center")
		{
			fielder = fieldingTeam.getCF();
		}

		return fielder;
	}

	//Triggers when a ball is hit and a fielder fails to make a catch, determines what the hit was and modfies the bases accordingly.
	void hitBall(int score, int basesRun) 
	{
		switch (basesRun)
		{
		case 1:
			if (onFirst) 
			{
				if (onSecond && onThird) 
				{
					score++;
				}
				else if (onSecond) {
					onThird = true;
				}
			}

			onFirst = true;
			cout << "Single!!!" << endl;
			break;

		case 2:
			if (onFirst)
			{
				if (onSecond && onThird)
				{
					score+=2;
				}
				else if (onSecond) {
					onThird = true;
					score++;
				}

				onThird = true;
				onFirst = false;
			}
			else if (onSecond) 
			{
				score++;
			}

			onSecond = true;
			cout << "Double!!!" << endl;
			break;

		case 3:
			if (onFirst) 
			{
				score++;
				onFirst = false;
			}
			if (onSecond) 
			{
				score++;
				onSecond = false;
			}
			if (onThird) 
			{
				score++;
			}

			onThird = true;
			cout << "Triple!!!" << endl;
			break;

		case 4:
			if (onFirst)
			{
				score++;
				onFirst = false;
			}
			if (onSecond)
			{
				score++;
				onSecond = false;
			}
			if (onThird)
			{
				score++;
				onThird = false;
			}

			score++;
			cout << "HOME RUN!!!" << endl;
			break;

		default:
			break;
		}
	}

	int determineChoice(string symbol) {
		if (symbol == "S" || symbol == "s") 
		{
			return 1;
		}
		else if (symbol == "R" || symbol == "r") 
		{
			return 2;
		}
		else if (symbol == "P" || symbol == "p") 
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}

public:
	Game() 
	{
		homeTeam = Team();
		awayTeam = Team();
		homeScore = 0;
		awayScore = 0;
	}

	Game(Team home, Team away)
	{
		homeTeam = home;
		awayTeam = away;
		homeScore = 0;
		awayScore = 0;
	}

	//Simulates an inning in baseball. Starts
	void playInning(bool finalInning) 
	{
		cout << awayTeam.getName() << " are batting." << endl;
		onField();

		if (finalInning == false || awayScore > homeScore) 
		{
			cout << homeTeam.getName() << " are batting." << endl;
			atBat();
		}
		
		cout << homeTeam.getName() << ": " << homeScore << endl;
		cout << awayTeam.getName() << ": " << awayScore << endl;
	}

	//Checks the final score and determines the winner of the game.
	void determineWinner() 
	{
		if (homeScore > awayScore) 
		{
			cout << homeTeam.getName() << " win!!!" << endl;
		}
		else if (homeScore < awayScore)
		{
			cout << awayTeam.getName() << " win!!!" << endl;
		}
		else 
		{
			cout << "The game is a draw!!!" << endl;
		}
	}

	string getHomeTeam() 
	{
		return homeTeam.getName();
	}

	string getAwayTeam()
	{
		return awayTeam.getName();
	}
};