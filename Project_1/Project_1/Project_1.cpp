#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameChoise
{
	stone = 1, paper = 2, scissorts = 3
};

enum enWinner 
{
	User=1,Computer=2,Draw=3
};

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoise UserChoise;
	enGameChoise ComputerChoice;
	enWinner RoundWinner;
	string RoundWinnerName = "";
};

struct stGameResults
{
	short GameRounds=0;
	short UserWinTimes=0;
	short ComputerWinTimes=0;
	short DrawTimes=0;
	enWinner GameWinner;
	string GameWinnerName = "";
};

short HowManyRounds()
{
	short RoundsNum;
	do
	{
		cout << "How Many Rounds You Want To play? (1-->10): \n";
		cin >> RoundsNum;

	} while (RoundsNum < 1 || RoundsNum>10);

	cout << endl;

	return RoundsNum;
}

int RandNumber(int from, int to)
{
	return rand() % (to - from + 1) + from;
}

enGameChoise GetComputerChoise()
{
	return (enGameChoise)RandNumber(1, 3);
}

enGameChoise ReadUserChoise()
{
	short UserChoice;

	do
	{
		cout << "Your Choice:[1]:Stone, [2]:Paper, [3]:Scissors?\n";
		cin >> UserChoice;

	} while (UserChoice<1 || UserChoice>3);

	return (enGameChoise)UserChoice;
}

string enumToName(enGameChoise GameChoice)
{
	string ArrGameChoice[3] = { "stone","paper","scissorts" };
	return ArrGameChoice[GameChoice - 1];
}

string WinnerName(enWinner Winner)
{
	string ArrWinnerName[3] = { "User","Computer","Draw" };
	return ArrWinnerName[Winner - 1];
}

enWinner WhoWinRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.UserChoise == RoundInfo.ComputerChoice)
		return enWinner::Draw;

	switch (RoundInfo.UserChoise)
	{
	case enGameChoise::stone:
		if (RoundInfo.ComputerChoice == enGameChoise::paper)
			return enWinner::Computer;
		break;
	case enGameChoise::paper:
		if (RoundInfo.ComputerChoice == enGameChoise::scissorts)
			return enWinner::Computer;
		break;
	case enGameChoise::scissorts:
		if (RoundInfo.ComputerChoice == enGameChoise::stone)
			return enWinner::Computer;
		break;
	}
	return enWinner::User;
}

enWinner WhoWinGame(short UserWinTimes, short ComputerWinTimes)
{
	if (UserWinTimes > ComputerWinTimes)
		return enWinner::User;
	else if (UserWinTimes < ComputerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}
 
void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::User:
		system("color 2f");//green
		break;
	case enWinner::Computer:
		cout << "\a"; //bill ring
		system("color 4f"); //red
		break;
	case enWinner::Draw:
		system("color 6f"); //yellow
		break;
	}
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n____________Round[" << RoundInfo.RoundNumber << "]____________\n";
	cout << "User Choice: " << enumToName(RoundInfo.UserChoise) << endl;
	cout << "Computert Choice: " << enumToName(RoundInfo.ComputerChoice) << endl;
	cout << "RoundWinner: [" << RoundInfo.RoundWinnerName << "]\n";
	cout << "--------------------------------\n" << endl;

	SetWinnerScreenColor(RoundInfo.RoundWinner);
}

stGameResults FillGameResults(short RoundsNum, short UserWinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = RoundsNum;
	GameResults.UserWinTimes = UserWinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWinGame(UserWinTimes, ComputerWinTimes);
	GameResults.GameWinnerName = WinnerName(WhoWinGame(UserWinTimes, ComputerWinTimes));

	return GameResults;
}

stGameResults PlayGame(short RoundsNum)
{
	stRoundInfo RoundInfo;

	short UserWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (int GameRound = 1; GameRound <= RoundsNum; GameRound++)
	{
		cout << "Round[" << GameRound << "] Begins:\n";

		RoundInfo.RoundNumber = GameRound;
		RoundInfo.UserChoise = ReadUserChoise();
		RoundInfo.ComputerChoice = GetComputerChoise();
		RoundInfo.RoundWinner = WhoWinRound(RoundInfo);
		RoundInfo.RoundWinnerName = WinnerName(RoundInfo.RoundWinner);

		if (RoundInfo.RoundWinner == enWinner::User)
			UserWinTimes++;

		else if (RoundInfo.RoundWinner == enWinner::Computer)
			ComputerWinTimes++;

		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(RoundsNum, UserWinTimes, ComputerWinTimes, DrawTimes);
}

void ShowGameOverScreen()
{
	cout << "\t\t\t" << "______________________________________________\n\n";
	cout <<"\t\t\t" << "             +++   Game Over   +++         \n";
	cout << "\t\t\t" <<"______________________________________________\n\n";
}

void ResetScreen()
{
	system("cls");//this make the consle clear and start from begin
	system("color 0f");//this make screen back to black
}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << "\t\t\t" << "________________[Game Results]________________\n\n";
	cout << "\t\t\t" << "Game Rounds: " << GameResults.GameRounds << endl;
	cout << "\t\t\t" << "User Won Times: " << GameResults.UserWinTimes << endl;
	cout << "\t\t\t" << "Computer Won Times: " << GameResults.ComputerWinTimes << endl;
	cout << "\t\t\t" << "Draw Times: " << GameResults.DrawTimes << endl;
	cout << "\t\t\t" << "Game Winner: " << GameResults.GameWinnerName << endl;
	cout << "\t\t\t" << "_______________________________________________\n\n";

	SetWinnerScreenColor(GameResults.GameWinner);
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(HowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);



		cout << "Do You Want To Play Again? (Y or N):\n";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}