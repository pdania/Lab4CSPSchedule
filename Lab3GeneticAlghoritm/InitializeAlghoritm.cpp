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

void ShowShedule(CSPAlgorithm& algorithm) {
	cout << "Here is Shedule:\n\n " << endl;

	for (size_t i = 0; i < algorithm.WeekDays().size(); i++)
	{
		std::map<int, std::string> weekDays = algorithm.WeekDays();
		cout << weekDays[i + 1] << ":\n" << endl;

		for (size_t k = 0; k < algorithm.PairTimes().size(); k++)
		{
			for (size_t p = 0; p < algorithm.Index().size(); p++)
			{
				for (size_t l = 0; l < algorithm.Index()[0].size(); l++)
				{
					size_t day = (p / 7);
					size_t pair = (p % 7);

					if (algorithm.Index()[p][l].course == nullptr)
						continue;
					if (day != i || pair != k)
						continue;
					std::map<int, std::string> pairTimes = algorithm.PairTimes();
					cout << pairTimes[k + 1] << ":" << endl;
					cout << "	PairType: " << (algorithm.Index()[p][l].isLection ? "Lection" : "Practice") << endl;
					cout << "	Professor: " << algorithm.Index()[p][l].professor->GetName() << endl;
					cout << "	Course: " << algorithm.Index()[p][l].course->GetName() << endl;
					cout << "	ClassRoom: " << algorithm.getConfig().GetRoomById(l)->GetName() << endl;
					cout << "	Group: " << algorithm.Index()[p][l].group->GetName() << endl;
					cout << "-------------------------" << endl;
				}
			}
		}
		cout << "***************************************************" << endl;
	}
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