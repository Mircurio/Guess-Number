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
			cout << "Прогресс успешно сохранён!" << endl;
		}
		else
		{
			cout << "Ошибка открытия файла. Данные не сохранены." << endl;
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
			cout << "Прогресс успешно загружен!" << endl;
		}
		else
		{
			cout << "Ошибка открытия файла. Данные не загружены." << endl;
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
		cout << "Добро пожаловать в игру \"Guess Number\"!" << endl;
		
		// Предлагать загружать сохранение только если его можно открыть.
		std::ifstream file;
		file.open(saveFileName);

		if (file.is_open())
		{
			int choice;
			cout << "Загрузить предыдущее сохранение? (0/1) ->";
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
				cout << "Хотите сохраниться и выйти? (0/1) -> ";
				cin >> choice;

				if (choice)
				{
					saveing();
					break;
				}
			}
		}

		cout << "Игра окончена! Вы набрали " << scores << " очков!" << endl;
		Sleep(5000);
	}

	void playRound()
	{
		cout << "Раунд " << round << "!" << endl;
		int userNumber = 0;
		int attempts = 0;

		while (userNumber != guessedNumber)
		{
			cout << "Введите чило: ";
			cin >> userNumber;

			if (userNumber > guessedNumber)
			{
				cout << "Ваше число больше загаданного." << endl;
			}
			else if (userNumber < guessedNumber)
			{
				cout << "Ваше число меньше загаданного." << endl;
			}

			++attempts;
		}

		cout << "Поздравляем!!! " << "Вы угадали число за " << attempts << " попыток!" << endl;
		cout << "Вы получили " << 10000 - (attempts - 1) * 400 << " очков!" << endl;

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