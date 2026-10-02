
#include <iostream>   
#include <cstdlib>    
#include <ctime>      

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResult
{
	short GameRounds;
	short Player1WinTimes;
	short ComputerWinTimes;
	short DrawTimes;
	enWinner GameWinner;
	string WinnerName;
};

short HowManyRounds()
{
	short GameRounds;
	do
	{
		cout << "How Many Rounds 1 to 10 ?\n";
		cin >> GameRounds;
	} while (GameRounds < 1 || GameRounds> 10);

	return GameRounds;
}

enGameChoice ReadPlayer1Choice()
{
	short Choice;
	do
	{
		cout << "\nYour Choice: [1]Stone, [2]Paper, [3]Scissors ? ";
		cin >> Choice;
	} while (Choice < 1 || Choice> 3);

	return enGameChoice(Choice);
}

short RandomNumber(short From, short To)
{
	short RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

enGameChoice GetComputerChoice()
{
	return enGameChoice(RandomNumber(1, 3));
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}

	return enWinner::Player1;
}

string WinnerName(enWinner Winner)
{
	string ArrWinnerName[3] = { "Player1","Computer","No Winner" };
	return ArrWinnerName[Winner - 1];

}

string ChoiceName(enGameChoice Choice)
{
	string ArrChoiceName[3] = { "Stone","Paper","Scissors" };
	return ArrChoiceName[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2f");
		break;
	case enWinner::Computer:
		system("color 4f");
		cout << "\a";
		break;
	case enWinner::Draw:
		system("color 6f");
		break;
	}
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
	cout << "\n_______________Round [" << RoundInfo.RoundNumber << "]---------------\n";
	cout << "\nPlayer1  Choice: " << ChoiceName(RoundInfo.Player1Choice);
	cout << "\nComputer Choice: " << ChoiceName(RoundInfo.ComputerChoice);
	cout << "\nRound Winner   : " << RoundInfo.WinnerName;
	cout << "\n--------------------------------------\n";

	SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else if (Player1WinTimes < ComputerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResult FillGameResult(short ManyRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResult GameResult;
	GameResult.GameRounds = ManyRounds;
	GameResult.Player1WinTimes = Player1WinTimes;
	GameResult.ComputerWinTimes = ComputerWinTimes;
	GameResult.DrawTimes = DrawTimes;
	GameResult.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);

	return GameResult;
}

stGameResult PlayGame(short ManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (int GameRound = 1;GameRound <= ManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";

		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResult(RoundInfo);
	}

	return FillGameResult(ManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);

}

string Tabs(short NumberOfTabs)
{
	string Tab = "";
	for (int i = 1;i <= NumberOfTabs;i++)
	{
		Tab += "\t";
	}
	return Tab;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "____________________________________________\n\n";
	cout << Tabs(2) << "            +++ G a m e  O v e r +++         \n";
	cout << Tabs(2) << "____________________________________________\n\n";
}

void ShowFinalGameResult(stGameResult GameResult)
{
	cout << Tabs(2) << "__________________ [Game Result] __________________\n";
	cout << Tabs(2) << "Game Rounds        : " << GameResult.GameRounds << endl;
	cout << Tabs(2) << "Player1 won times  : " << GameResult.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer Won times : " << GameResult.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw times         : " << GameResult.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << GameResult.WinnerName << endl;
	cout << Tabs(2) << "___________________________________________________\n\n";

	SetWinnerScreenColor(GameResult.GameWinner);
}

void ResetScreen()
{
	system("cls");
	system("color 0f");
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameResult GameResult = PlayGame(HowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResult(GameResult);

		cout << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{

	srand((unsigned)time(NULL));

	StartGame();


	return 0;

}