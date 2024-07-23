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

string ReadPlayerName(string Message)
{
    string Name = "";
    cout << Message << endl;
    cin >> Name;
    return Name;
}

int ReadPositiveNumber(string message)
{
    int Number = 0;
    do
    {
        cout << message << endl;
        cin >> Number;
    } while (10 < Number || Number <= 0);

    return Number;
}

int RandomNumber(int from, int to)
{
    return rand() % (to + 1 - from) + from;
}

int ReadPlayerChoice()
{
    int Number = 0;
    do
    {
        cout << "Your Choice : [1]Stone , [2]Paper , [3]Scissor ? ";
        cin >> Number;
    } while (Number <= 0 || Number > 3);
    return Number;
}

void FillPlayerChoice(int Number, strPlayerInfo &Player)
{
        Player.PlayerChoice = (enGameChoice)Number;
}

void AddRoundResult(strGameDashboard &Dashboard)
{
    enGameChoice Player1Choice = Dashboard.Player1.PlayerChoice;
    enGameChoice Player2Choice = Dashboard.Player2.PlayerChoice;
    if (Player1Choice == Player2Choice)
    {
        Dashboard.Draw += 1;
        Dashboard.RoundResult = enRoundResult::Draw;
    }
    else if (Player1Choice == enGameChoice::Paper && Player2Choice == enGameChoice::Stone)
    {
        Dashboard.Player1.Wins += 1;
        Dashboard.RoundResult = enRoundResult::Player1Win;
    }
    else if (Player1Choice == enGameChoice::Stone && Player2Choice == enGameChoice::Scissor)
    {
        Dashboard.Player1.Wins += 1;
        Dashboard.RoundResult = enRoundResult::Player1Win;
    }
    else if (Player1Choice == enGameChoice::Scissor && Player2Choice == enGameChoice::Paper)
    {
        Dashboard.Player1.Wins += 1;
        Dashboard.RoundResult = enRoundResult::Player1Win;
    }
    else
    {
        Dashboard.Player2.Wins += 1;
        Dashboard.RoundResult = enRoundResult::Player2Win;
    }
}

string PrintPlayerChoice(strPlayerInfo Player)
{
    switch (Player.PlayerChoice)
    {
    case enGameChoice::Paper:
        return "Paper";
    case enGameChoice::Stone:
        return "Stone";
    case enGameChoice::Scissor:
        return "Scissor";
    }
    return "";
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

void GameResultHeader(string Title)
{
    cout << "\n\n\t\t______________________________________________________\n\n";
    cout << "\t\t\t\t   *** " << Title << " ***";
    cout << "\n\t\t______________________________________________________\n";
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
    cout << "\n\t\t___________________[ Game Results ]___________________\t\t\n\n";
    cout << "\t\t" << "Game Rounds\t\t: " << Dashboard.TotalRounds << endl;
    cout << "\t\t" << Dashboard.Player1.Name << " won times\t: " << Dashboard.Player1.Wins << endl;
    cout << "\t\t" << Dashboard.Player2.Name << " won times\t: " << Dashboard.Player2.Wins << endl;
    cout << "\t\t" << "Draw times\t\t: " << Dashboard.Draw << endl;
    cout << "\t\t" << "Final Winner\t\t: " << PrintFinalWinner(Dashboard) << endl;
    cout << "\t\t" << "______________________________________________________" << endl;
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
    cout << Dashboard.Player1.Name << " Choice : " << PrintPlayerChoice(Dashboard.Player1) << endl;
    cout << Dashboard.Player2.Name << " Choice : " << PrintPlayerChoice(Dashboard.Player2) << endl;
    cout << "Round Winner\t: " << "[ " << PrintRoundWinner(Dashboard) << " ]" << endl;
    cout << "___________________________________________\n"
         << endl;
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
    strGameDashboard Dashboard;
    Dashboard.Player1.Name = ReadPlayerName("Please enter Your Name ? ");
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