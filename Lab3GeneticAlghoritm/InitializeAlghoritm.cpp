#include"InitializeAlghoritm.h"

bool IsDigit(string str) {
	return !str.empty() &&
		find_if(str.begin(), str.end(), [](char c) { return !isdigit(c); }) == str.end();
}

void ShowStartingWindwow(size_t& crossoverProbability, size_t& mutationProbability, size_t& pairCount) {
	size_t crossoserPoints = 0;
	SetCursorPosition(2, 0);
	cout << "Building schedule with Genetic algorithm  (Osadchuk, Parkhomenko, 2020)";

	SetCursorPosition(0, 3, Color::White);
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

		ClearLine(3);
		SetCursorPosition(0, 3, Color::Cyan);
		cout << "Choose number between 0 and 100: ";
	}

	SetCursorPosition(0, 4, Color::White);
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

		ClearLine(4);
		SetCursorPosition(0, 4, Color::Cyan);
		cout << "Choose number between 0 and 100: ";
	}
	SetCursorPosition(0, 5, Color::White);
	cout << "Enter number of pairs in week (1-35): ";
	while (true) {
		string pairCt;
		cin >> pairCt;

		if (IsDigit(pairCt)) {
			pairCount = atoi(pairCt.c_str());
			if (pairCount > 0 && pairCount <= 35) {
				break;
			}
		}

		ClearLine(5);
		SetCursorPosition(0, 5, Color::Cyan);
		cout << "Choose number between 1 and 35: ";
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