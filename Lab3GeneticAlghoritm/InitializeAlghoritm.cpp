#include"InitializeAlghoritm.h"

bool IsDigit(string str) {
	return !str.empty() &&
		find_if(str.begin(), str.end(), [](char c) { return !isdigit(c); }) == str.end();
}

void ShowStartingWindwow(size_t& pairCount) {
	size_t crossoserPoints = 0;
	SetCursorPosition(2, 0);
	cout << "Building schedule with CSP (Osadchuk, Parkhomenko, 2020)";

	SetCursorPosition(0, 3, Color::White);
	cout << "Enter number of pairs in week (1-50): ";
	while (true) {
		string pairCt;
		cin >> pairCt;

		if (IsDigit(pairCt)) {
			pairCount = atoi(pairCt.c_str());
			if (pairCount > 0 && pairCount <= 50) {
				break;
			}
		}

		ClearLine(3);
		SetCursorPosition(0, 3, Color::Cyan);
		cout << "Choose number between 1 and 50: ";
	}
	SetCursorPosition(0, 4, Color::White);
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