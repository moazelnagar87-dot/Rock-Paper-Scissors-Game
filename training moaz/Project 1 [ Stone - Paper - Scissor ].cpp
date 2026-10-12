#include <iostream>
#include <cstdlib>

using namespace std;

enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct stQuestionInfo
{
	int Number1;
	int Number2;
	enOperationType OpType;
	enQuestionLevel QuestionLevel;
	int UserAnswar;
	int QuestionAnswar;
	char OpSignal;
};
struct stQuizInfo
{
	short NumberOfQuestion = 0, RightAnswers = 0, WrongAnswers = 0;
	string QuestionLevelNa;
	string OpTypeNa;

};

short HowManyQuestion()
{
	short NumberOfQuestion = 1;

	do
	{
		cout << "How Many Question do you want to answer ? ";
		cin >> NumberOfQuestion;
	} while (NumberOfQuestion < 1 || NumberOfQuestion > 10);

	return NumberOfQuestion;
}

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;

	return RandNum;
}

enQuestionLevel ReadQuestionLevel()
{
	short QuestionLevel = 0;
	do
	{
		cout << "Enter Question Level : [1] Easy, [2] Med, [3] Hard, [4] Mix : ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOperationType()
{
	short OperationType = 0;
	do
	{
		cout << "Enter Operation Type : [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix : ";
		cin >> OperationType;
	} while (OperationType < 1 || OperationType > 5);
	return (enOperationType)OperationType;
}

string QuestionLevelName(enQuestionLevel QuestionLevel)
{
	string QuestionLevelNa[4] = { "Easy","Med","Hard","Mix" };
	return QuestionLevelNa[QuestionLevel - 1];
}
string OpTypeName(enOperationType OperationType)
{
	string OpTypeNa[5] = { "Add","Sub","Mult","Div","Mix" };
	return OpTypeNa[OperationType - 1];
}

void FillQuestionInfo(stQuestionInfo& QuestionInfo, enOperationType OpType, enQuestionLevel QuestionLevel)
{
	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		QuestionInfo.Number1 = RandomNumber(1, 10);
		QuestionInfo.Number2 = RandomNumber(1, 10);
		break;
	case enQuestionLevel::Med:
		QuestionInfo.Number1 = RandomNumber(10, 50);
		QuestionInfo.Number2 = RandomNumber(10, 50);
		break;
	case enQuestionLevel::Hard:
		QuestionInfo.Number1 = RandomNumber(50, 100);
		QuestionInfo.Number2 = RandomNumber(50, 100);
		break;
	case enQuestionLevel::Mix:
		QuestionInfo.Number1 = RandomNumber(1, 100);
		QuestionInfo.Number2 = RandomNumber(1, 100);
		break;
	}

	if (OpType == enOperationType::MixOp)
	{
		OpType = enOperationType(RandomNumber(1, 4));
	}

	switch (OpType)
	{
	case enOperationType::Add:
		QuestionInfo.OpSignal = '+';
		QuestionInfo.QuestionAnswar = QuestionInfo.Number1 + QuestionInfo.Number2;
		break;
	case enOperationType::Sub:
		QuestionInfo.OpSignal = '-';
		QuestionInfo.QuestionAnswar = QuestionInfo.Number1 - QuestionInfo.Number2;
		break;
	case enOperationType::Mul:
		QuestionInfo.OpSignal = '*';
		QuestionInfo.QuestionAnswar = QuestionInfo.Number1 * QuestionInfo.Number2;
		break;
	case enOperationType::Div:
		QuestionInfo.OpSignal = '/';
		QuestionInfo.QuestionAnswar = QuestionInfo.Number1 / QuestionInfo.Number2;
		break;
	}

}

string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 1; i < NumberOfTabs; i++)
	{
		t = t + "\t";
	}
	return t;
}

void ShowQuestionResult(stQuestionInfo QuestionInfo, stQuizInfo& QuizInfo)
{
	if (QuestionInfo.QuestionAnswar == QuestionInfo.UserAnswar)
	{
		system("color 2F");
		cout << "Right Answar :-)";

		QuizInfo.RightAnswers++;
	}
	else
	{
		system("color 4F");
		cout << "Wrong Answar :-(" << endl;
		cout << "The Right Answar is " << QuestionInfo.QuestionAnswar << endl;

		QuizInfo.WrongAnswers++;
	}
}

void PrintQuestions(stQuestionInfo& QuestionInfo, stQuizInfo& QuizInfo)
{
	cout << Tabs(1) << QuestionInfo.Number1 << endl;
	cout << Tabs(1) << QuestionInfo.Number2 << Tabs(2) << QuestionInfo.OpSignal << "\n";
	cout << "__________\n";
	cin >> QuestionInfo.UserAnswar;
	ShowQuestionResult(QuestionInfo, QuizInfo);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void PlayGame(stQuestionInfo& QuestionInfo, stQuizInfo& QuizInfo)
{
	QuizInfo.NumberOfQuestion = HowManyQuestion();
	QuestionInfo.QuestionLevel = ReadQuestionLevel();
	QuestionInfo.OpType = ReadOperationType();

	for (int i = 1; i <= QuizInfo.NumberOfQuestion; i++)
	{
		FillQuestionInfo(QuestionInfo, QuestionInfo.OpType, QuestionInfo.QuestionLevel);

		cout << "\n\nQuestion [" << i << "/" << QuizInfo.NumberOfQuestion << "]\n\n";

		PrintQuestions(QuestionInfo, QuizInfo);
	}
}

void ShowFinalQuizResults(stQuizInfo QuizInfo, stQuestionInfo QuestionInfo)
{


	QuizInfo.QuestionLevelNa = QuestionLevelName(QuestionInfo.QuestionLevel);
	QuizInfo.OpTypeNa = OpTypeName(QuestionInfo.OpType);

	if (QuizInfo.RightAnswers > QuizInfo.WrongAnswers)
	{
		cout << "\n\n___________________________________________\n\n";
		cout << Tabs(2) << "Final Results is Pass :-)";
		cout << "\n\n___________________________________________\n\n";
	}
	else
	{
		cout << "\n\n___________________________________________\n\n";
		cout << Tabs(2) << "Final Results is Fail :-(";
		cout << "\n\n___________________________________________\n\n";
	}
	cout << "\n";

	cout << "Number Of Questions : " << QuizInfo.NumberOfQuestion << endl;
	cout << "Questions Level : " << QuizInfo.QuestionLevelNa << endl;
	cout << "OpType : " << QuizInfo.OpTypeNa << endl;
	cout << "Number Of Right Answars : " << QuizInfo.RightAnswers << endl;
	cout << "Number Of Wrong Answars : " << QuizInfo.WrongAnswers << endl;

	cout << "\n\n___________________________________________\n\n";
}

void StartGame()
{
	stQuestionInfo QuestionInfo;
	stQuizInfo QuizInfo;

	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayGame(QuestionInfo, QuizInfo);
		ShowFinalQuizResults(QuizInfo, QuestionInfo);
		cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}