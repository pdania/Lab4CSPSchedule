#include"InitializeAlghoritm.h"

bool IsDigit(string str) {
	return !str.empty() &&
		find_if(str.begin(), str.end(), [](char c) { return !isdigit(c); }) == str.end();
}

void ShowStartingWindwow(size_t& algorithmType, size_t& pairCount) {
	SetCursorPosition(2, 0);
	cout << "Building schedule with CSP  (Osadchuk, Parkhomenko, 2020)";
	SetCursorPosition(0, 2);
	cout << "Choose one of the proposed heuristic:" << endl;
	cout << "Minimum Remaining Values - 1" << endl;
	cout << "Degree heuristics - 2" << endl;
	cout << "Least constraining value - 3" << endl;
	cout << "Forward checking - 4" << endl;
	cout << "Constraint propagation - 5" << endl;
	cout << "Our best solution - 6" << endl;
	cout << "Exit - 0" << endl;

	SetCursorPosition(0, 11, Color::Yellow);
	cout << "Your choice: ";

	while (true) { // read algorithm number
		string algorithm_str;
		cin >> algorithm_str;

		if (IsDigit(algorithm_str)) {
			algorithmType = atoi(algorithm_str.c_str());
			if (algorithmType >= 0 && algorithmType <= 5) {
				if (algorithmType == 0) {
					exit(0);
				}
				break;
			}
		}

		ClearLine(11);
		SetCursorPosition(0, 11, Color::Cyan);
		cout << "Choose number between (1, 2, 3, 4, 5, 0): ";
	}
	SetCursorPosition(0, 12, Color::White);
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

		ClearLine(12);
		SetCursorPosition(0, 12, Color::Cyan);
		cout << "Choose number between 1 and 35: ";
	}
	SetCursorPosition(0, 13, Color::White);
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