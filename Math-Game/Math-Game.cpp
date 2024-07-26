#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameLevel
{
	Easy = 1,
	Med,
	Hard,
	Mix
};
enum enOperationType
{
	Add = 1,
	Sub,
	Mul,
	Div,
	mix
};

struct strQuestionInfo
{
	float RightAnswer = 0, PlayerAnswer = 0;
	bool Result = false;
};

struct strGameDashboard
{
	short TotalQuestions = 0, RightAnswers = 0, WrongAnswers = 0;
	enGameLevel Level;
	enOperationType OpType;
	strQuestionInfo QuestionInfo;
};

short ReadPositiveNumber(string message)
{
	short Number = 0;
	do
	{
		cout << message;
		cin >> Number;
	} while (100 < Number || Number <= 0);
	return Number;
}

int RandomNumber(int from, int to)
{
	return rand() % (to + 1 - from) + from;
}

short ReadPlayerChoice(string Message, short NumberOfChoices)
{
	short Number = 0;
	do
	{
		cout << Message;
		cin >> Number;
	} while (Number <= 0 || Number > NumberOfChoices);
	return Number;
}

void PrintQuestion(short Num1, short Num2, char operation)
{
	cout << "\n"
		<< Num1 << "\n"
		<< Num2 << " " << operation << "\n____________" << endl;
}

float GetQuestion(enGameLevel Level, enOperationType OpType)
{
	short Num1 = 0, Num2 = 0, From = 0, To = 0;
	if (Level == enGameLevel::Mix)
		Level = (enGameLevel)RandomNumber(1, 3);
	switch (Level)
	{
	case enGameLevel::Easy:
		From = 1, To = 10;
		break;
	case enGameLevel::Med:
		From = 10, To = 50;
		break;
	case enGameLevel::Hard:
		From = 50, To = 100;
		break;
	}

	Num1 = RandomNumber(From, To), Num2 = RandomNumber(From, To);

	if (OpType == enOperationType::mix)
		OpType = (enOperationType)RandomNumber(1, 4);
	switch (OpType)
	{
	case enOperationType::Add:
		PrintQuestion(Num1, Num2, '+');
		return Num1 + Num2;
	case enOperationType::Sub:
		PrintQuestion(Num1, Num2, '-');
		return Num1 - Num2;
	case enOperationType::Mul:
		PrintQuestion(Num1, Num2, '*');
		return Num1 * Num2;
	case enOperationType::Div:
		PrintQuestion(Num1, Num2, '/');
		return Num1 / Num2;
	}
}

float ReadPlayerAnswer()
{
	float Answer = 0;
	cin >> Answer;
	return Answer;
}

void FillResult(strGameDashboard& Dashboard)
{
	if (Dashboard.QuestionInfo.PlayerAnswer == Dashboard.QuestionInfo.RightAnswer)
		Dashboard.RightAnswers++, Dashboard.QuestionInfo.Result = true;
	else
		Dashboard.WrongAnswers++, Dashboard.QuestionInfo.Result = false;
}

void ScreenColor(bool Result)
{
	if (Result)
		system("color 2F");
	else
		system("color 4F");
}

void PrintResult(bool Result, float RightAnswer)
{
	ScreenColor(Result);
	if (Result)
		cout << "Right Answer :-)\n"
		<< endl;
	else
	{
		cout << "Wrong answer :-(" << endl;
		cout << "The right answer is : " << RightAnswer << endl;
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

bool IsPass(short RightAnswers, short WrongAnswers)
{
	return (RightAnswers > WrongAnswers);
}

void GameResultHeader(bool IsPass)
{
	string Grade = "";
	if (IsPass)
		Grade = "Pass :-)";
	else
		Grade = "Fail :-(";
	cout << "\n\n"
		<< Tabs(2) << "______________________________________________________\n\n";
	cout << Tabs(3) << "   *** Final Result is " << Grade << " ***";
	cout << "\n"
		<< Tabs(2) << "______________________________________________________\n";
}

string PrintGameLevel(enGameLevel GameLevel)
{
	string Levels[4] = { "Easy", "Med", "Hard", "Mix" };
	return Levels[GameLevel - 1];
}
string PrintOperationType(enOperationType OpType)
{
	string Levels[5] = { "+", "-", "*", "/", "Mix" };
	return Levels[OpType - 1];
}

void PrintGameResult(strGameDashboard Dashboard)
{
	cout << "\n"
		<< Tabs(2) << "___________________[ Game Results ]___________________" << Tabs(2) << "\n\n";
	cout << Tabs(2) << "Number Of Questions" << Tabs(1) << ": " << Dashboard.TotalQuestions << endl;
	cout << Tabs(2) << "Questions Level" << Tabs(2) << ": " << PrintGameLevel(Dashboard.Level) << endl;
	cout << Tabs(2) << "OpType" << Tabs(3) << ": " << PrintOperationType(Dashboard.OpType) << endl;
	cout << Tabs(2) << "Number of Right Answers" << Tabs(1) << ": " << Dashboard.RightAnswers << endl;
	cout << Tabs(2) << "Number of Wrong Answers" << Tabs(1) << ": " << Dashboard.WrongAnswers << endl;
	cout << Tabs(2) << "______________________________________________________" << endl;
}

void PrintGameDashboard(strGameDashboard Dashboard)
{
	GameResultHeader(IsPass(Dashboard.RightAnswers, Dashboard.WrongAnswers));
	PrintGameResult(Dashboard);
}

bool PlayAgain()
{
	string Answer = "";
	cout << "\nDo You want to play again ? ( Y / N )" << endl;
	cin >> Answer;
	cout << endl;
	return (Answer == "y" || Answer == "Y");
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void FillGameRules(strGameDashboard& Dashboard)
{
	Dashboard.TotalQuestions = ReadPositiveNumber("How many questions do you want to answer ? ");
	Dashboard.Level = (enGameLevel)ReadPlayerChoice("Enter questions level [1]Easy , [2]Mid , [3]Hard , [4]Mix ? ", 4);
	Dashboard.OpType = (enOperationType)ReadPlayerChoice("Enter Operation Type [1]Add , [2]Sub , [3]Mul , [4]Div , [5]Mix ? ", 5);
}

void StartGame()
{
	ResetScreen();
	strGameDashboard Dashboard;
	FillGameRules(Dashboard);
	for (int i = 1; i <= Dashboard.TotalQuestions; i++)
	{
		cout << "\nQuestion [" << i << "/" << Dashboard.TotalQuestions << "]" << endl;
		Dashboard.QuestionInfo.RightAnswer = GetQuestion(Dashboard.Level, Dashboard.OpType);
		Dashboard.QuestionInfo.PlayerAnswer = ReadPlayerAnswer();
		FillResult(Dashboard);
		PrintResult(Dashboard.QuestionInfo.Result, Dashboard.QuestionInfo.RightAnswer);
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