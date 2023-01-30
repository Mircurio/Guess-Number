#include <iostream>
#include <time.h>
#include <fstream>
#include <Windows.h>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::cin;

const string saveFileName = "Guess_Number_save.txt";
const int maxRound = 5;

class Save
{
	int round;
	int scores;
public:
	Save(int round, int scores) : round{ round }, scores{ scores } {};
	Save() : Save(1, 0) {};

	void Saveing()
	{
		std::ofstream file;
		file.open(saveFileName, std::ios::out);

		if (file.is_open())
		{
			file << round << "\n" << scores << endl;
			cout << "�������� ������� �������!" << endl;
		}
		else
		{
			cout << "������ �������� �����. ������ �� ���������." << endl;
		}

		file.close();
	}

	void Loading()
	{
		std::ifstream file;
		file.open(saveFileName, std::ios::in);

		if (file.is_open())
		{
			file >> round >> scores;
			cout << "�������� ������� ��������!" << endl;
		}
		else
		{
			cout << "������ �������� �����. ������ �� ���������." << endl;
		}

		file.close();
	}

	int getRound()
	{
		return round;
	}

	void setRound(int round)
	{
		this->round = round;
	}

	int getScores()
	{
		return scores;
	}

	void setScores(int scores)
	{
		this->scores = scores;
	}
};


class Game
{
	int guessedNumber;
	int scores;
	int round;

	void saveing()
	{
		Save save(round, scores);
		save.Saveing();
	}

	void loading()
	{
		Save save;
		save.Loading();

		scores = save.getScores();
		round = save.getRound();
	}

public:

	Game() : scores{ 0 }, round{ 1 }
	{
		generateNum();
	}

	void playGame()
	{
		cout << "����� ���������� � ���� \"Guess Number\"!" << endl;
		
		// ���������� ��������� ���������� ������ ���� ��� ����� �������.
		std::ifstream file;
		file.open(saveFileName);

		if (file.is_open())
		{
			int choice;
			cout << "��������� ���������� ����������? (0/1) ->";
			cin >> choice;

			if (choice)
			{
				loading();
			}
		}

		file.close();

		Sleep(2500);
		system("cls");

		while (round <= maxRound)
		{
			playRound();
			generateNum();
			
			if (round < maxRound)
			{
				int choice;
				cout << "������ ����������� � �����? (0/1) -> ";
				cin >> choice;

				if (choice)
				{
					saveing();
					break;
				}
			}
		}

		cout << "���� ��������! �� ������� " << scores << " �����!" << endl;
		Sleep(5000);
	}

	void playRound()
	{
		cout << "����� " << round << "!" << endl;
		int userNumber = 0;
		int attempts = 0;

		while (userNumber != guessedNumber)
		{
			cout << "������� ����: ";
			cin >> userNumber;

			if (userNumber > guessedNumber)
			{
				cout << "���� ����� ������ �����������." << endl;
			}
			else if (userNumber < guessedNumber)
			{
				cout << "���� ����� ������ �����������." << endl;
			}

			++attempts;
		}

		cout << "�����������!!! " << "�� ������� ����� �� " << attempts << " �������!" << endl;
		cout << "�� �������� " << 10000 - (attempts - 1) * 400 << " �����!" << endl;

		scores += 10000 - (attempts - 1) * 400;
		++round;

		Sleep(4000);
		system("cls");
	}

	void generateNum(int start = 1, int end = 100)
	{
		guessedNumber = rand() % (end - start + 1) + start;
	}
};

int main()
{
	setlocale(0, "");
	srand(time(NULL));

	Game game;
	game.playGame();

	return 0;
}