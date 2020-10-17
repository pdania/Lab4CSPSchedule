#include"InitializeAlghoritm.h"

bool IsDigit(string str) {
	return !str.empty() &&
		find_if(str.begin(), str.end(), [](char c) { return !isdigit(c); }) == str.end();
}

void ShowStartingWindwow() {
	size_t crossoserPoints = 0;
	SetCursorPosition(2, 0);
	cout << "Building schedule with Genetic algorithm  (Osadchuk, Parkhomenko, 2020)";

	SetCursorPosition(0, 2, Color::White);
	cout << "Enter number of crossover points (0-??): ";

	while (true) {
		string crossover_str;
		cin >> crossover_str;

		if (IsDigit(crossover_str)) {
			crossoserPoints = atoi(crossover_str.c_str());
			if (crossoserPoints >= 0 && true) {
				break;
			}
		}

		ClearLine(2);
		SetCursorPosition(0, 2, Color::Cyan);
		cout << "Choose number between 0 and ??: ";
	}
	size_t mutationSize = 0;
	SetCursorPosition(0, 3, Color::White);
	cout << "Enter mutation size (0-??): ";
	while (true) {
		string mutation;
		cin >> mutation;

		if (IsDigit(mutation)) {
			mutationSize = atoi(mutation.c_str());
			if (mutationSize >= 0 && true) {
				break;
			}
		}

		ClearLine(3);
		SetCursorPosition(0, 3, Color::Cyan);
		cout << "Choose number between 0 and ??: ";
	}

	size_t crossoverProbability = 0;
	SetCursorPosition(0, 4, Color::White);
	cout << "Enter crossover probability (0-100): ";
	while (true) {
		string crossProbability;
		cin >> crossProbability;

		if (IsDigit(crossProbability)) {
			crossoverProbability = atoi(crossProbability.c_str());
			if (crossoverProbability >= 0 && crossoverProbability <=100) {
				break;
			}
		}

		ClearLine(4);
		SetCursorPosition(0, 4, Color::Cyan);
		cout << "Choose number between 0 and 100: ";
	}

	size_t mutationProbability = 0;
	SetCursorPosition(0, 5, Color::White);
	cout << "Enter mutation probability (0-100): ";
	while (true) {
		string mutProbability;
		cin >> mutProbability;

		if (IsDigit(mutProbability)) {
			mutationProbability = atoi(mutProbability.c_str());
			if (mutationProbability >= 0 && mutationProbability <= 100) {
				break;
			}
		}

		ClearLine(5);
		SetCursorPosition(0, 5, Color::Cyan);
		cout << "Choose number between 0 and 100: ";
	}

	SetCursorPosition(0, 6, Color::White);
	cout << "Press any button to start!";

	system("pause >> NUL");
	system("cls");
}

void SetCursorPosition(const int x, const int y, const Color color) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, static_cast<int>(color));
	cout.flush();
	SetConsoleCursorPosition(hOut, { (SHORT)x, (SHORT)y });
}

void ClearLine(const size_t y) {
	for (int x = 0; x < 20; x++) {
		SetCursorPosition(x * 10, y);
		cout << "          ";
	}
}