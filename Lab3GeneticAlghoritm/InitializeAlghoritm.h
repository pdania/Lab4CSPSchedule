#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <cassert>
#include <fstream>

using namespace std;



enum class Color {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15,
};

bool IsDigit(string str);
void ShowStartingWindwow(size_t& algorithmType, size_t& pairCount);
void SetCursorPosition(const int x, const int y, const Color color = Color::White);
void ClearLine(const size_t y);

