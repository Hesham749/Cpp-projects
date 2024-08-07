#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameChoice
{
	Stone = 1,
	Paper,
	Scissor
};

enum enRoundResult
{
	Player1Win = 1,
	Player2Win,
	Draw
};

struct strPlayerInfo
{
	string Name;
	int Wins = 0;
	enGameChoice PlayerChoice;
};

struct strGameDashboard
{
	strPlayerInfo Player1, Player2;
	int Draw = 0, TotalRounds = 0;
	enRoundResult RoundResult;
};

short ReadPositiveNumber(string message)
{
	short Number = 0;
	cout << message;
	cin >> Number;
	while (cin.fail() || (Number > 10 || Number <= 0))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "invalid Number please enter valid Number ? ";
		cin >> Number;
	}
	return Number;
}

int RandomNumber(int from, int to)
{
	return rand() % (to + 1 - from) + from;
}

int ReadPlayerChoice()
{
	int Number = 0;
	cout << "Your Choice : [1]Stone , [2]Paper , [3]Scissor ? ";
	cin >> Number;
	while (cin.fail() || (Number > 3 || Number < 1))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "invalid Number please enter valid Number ? ";
		cin >> Number;
	}
	return Number;
}

void FillPlayerChoice(int Number, strPlayerInfo& Player)
{
	Player.PlayerChoice = (enGameChoice)Number;
}

void AddRoundResult(strGameDashboard& Dashboard)
{
	enGameChoice Player1Choice = Dashboard.Player1.PlayerChoice;
	enGameChoice Player2Choice = Dashboard.Player2.PlayerChoice;
	if (Player1Choice == Player2Choice)
	{
		Dashboard.Draw += 1;
		Dashboard.RoundResult = enRoundResult::Draw;
	}
	else {
		switch (Player1Choice)
		{
		case enGameChoice::Paper:
			if (Player2Choice == enGameChoice::Stone)
			{
				Dashboard.Player1.Wins += 1;
				Dashboard.RoundResult = enRoundResult::Player1Win;
			}
			break;
		case enGameChoice::Stone:
			if (Player2Choice == enGameChoice::Scissor)
			{
				Dashboard.Player1.Wins += 1;
				Dashboard.RoundResult = enRoundResult::Player1Win;
			}
			break;
		case enGameChoice::Scissor:
			if (Player2Choice == enGameChoice::Paper)
			{
				Dashboard.Player1.Wins += 1;
				Dashboard.RoundResult = enRoundResult::Player1Win;
			}
			break;
		default:
			Dashboard.Player2.Wins += 1;
			Dashboard.RoundResult = enRoundResult::Player2Win;
			break;
		}
	}
}

string PrintPlayerChoice(strPlayerInfo Player)
{
	string choice[3] = { "Stone", "Paper", "Scissor" };
	return choice[Player.PlayerChoice - 1];
}

string PrintRoundWinner(strGameDashboard Dashboard)
{
	switch (Dashboard.RoundResult)
	{
	case enRoundResult::Player1Win:
		system("color 2F");
		return Dashboard.Player1.Name;
	case enRoundResult::Player2Win:
		cout << "\a";
		system("color 4F");
		return Dashboard.Player2.Name;
	default:
		system("color 6F");
		return "No Winner";
	}
}
string Tabs(short NumberOfTabs)
{
	string tab = "";
	for (int i = 0; i < NumberOfTabs; i++)
	{
		tab += "\t";
	}
	return tab;
}

void GameResultHeader(string Title)
{
	cout << "\n\n"
		<< Tabs(2) << "______________________________________________________\n\n";
	cout << Tabs(4) << "   *** " << Title << " ***";
	cout << "\n"
		<< Tabs(2) << "______________________________________________________\n";
}

string PrintFinalWinner(strGameDashboard Dashboard)
{
	if (Dashboard.Player1.Wins > Dashboard.Player2.Wins)
		return Dashboard.Player1.Name;
	else if (Dashboard.Player2.Wins > Dashboard.Player1.Wins)
		return Dashboard.Player2.Name;
	else
		return "No Winner";
}

void PrintGameResult(strGameDashboard Dashboard)
{
	cout << "\n"
		<< Tabs(2) << "___________________[ Game Results ]___________________" << Tabs(2) << "\n\n";
	cout << Tabs(2) << "Game Rounds" << Tabs(2) << ": " << Dashboard.TotalRounds << endl;
	cout << Tabs(2) << Dashboard.Player1.Name << " won times" << Tabs(1) << ": " << Dashboard.Player1.Wins << endl;
	cout << Tabs(2) << Dashboard.Player2.Name << " won times" << Tabs(1) << ": " << Dashboard.Player2.Wins << endl;
	cout << Tabs(2) << "Draw times" << Tabs(2) << ": " << Dashboard.Draw << endl;
	cout << Tabs(2) << "Final Winner" << Tabs(2) << ": " << PrintFinalWinner(Dashboard) << endl;
	cout << Tabs(2) << "______________________________________________________" << endl;
}

void PrintGameDashboard(strGameDashboard Dashboard)
{
	GameResultHeader("Game Over");
	PrintGameResult(Dashboard);
}

void PrintRoundResult(strGameDashboard Dashboard, int RoundNumber)
{
	cout << "\n\n_________________Round [" << RoundNumber << "]" << "_________________\n"
		<< endl;
	cout << Dashboard.Player1.Name << " Choice   : " << PrintPlayerChoice(Dashboard.Player1) << endl;
	cout << Dashboard.Player2.Name << " Choice : " << PrintPlayerChoice(Dashboard.Player2) << endl;
	cout << "Round Winner\t: " << "[ " << PrintRoundWinner(Dashboard) << " ]" << endl;
	cout << "___________________________________________\n"
		<< endl;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

bool PlayAgain()
{
	string Answer = "";
	cout << "\nDo You want to play again ? ( Y / N )" << endl;
	cin >> Answer;
	cout << endl;
	return (Answer == "y" || Answer == "Y");
}

void StartGame()
{
	ResetScreen();
	strGameDashboard Dashboard;
	Dashboard.Player1.Name = "Player";
	Dashboard.Player2.Name = "Computer";
	Dashboard.TotalRounds = ReadPositiveNumber("How many rounds you want to Play : 1 to 10 ? ");
	for (int i = 1; i <= Dashboard.TotalRounds; i++)
	{
		cout << "\nRound [" << i << "] begins : " << endl;
		FillPlayerChoice(ReadPlayerChoice(), Dashboard.Player1);
		FillPlayerChoice(RandomNumber(1, 3), Dashboard.Player2);
		AddRoundResult(Dashboard);
		PrintRoundResult(Dashboard, i);
	}
	PrintGameDashboard(Dashboard);
	if (PlayAgain())
		StartGame();
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}