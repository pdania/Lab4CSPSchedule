#pragma once
#include "Config.h"
#include "Course.h"
#include "Room.h"
#include "StudentsGroup.h"
#include "Professor.h"
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include<iostream>

class CSPAlgorithm {
public:

public:

	CSPAlgorithm(Config& config, size_t pairCount);

	void Init();

	bool CheckPairs();

	void AddPairs();

	void ProcessAlgorithm();

	void PrintSchedule();

private:
	Config& _config;
	std::vector<std::string> _population;

	map<int, std::string> pairTimes = {
		{1,"8:00-9:50"},
		{2,"10:00-11:20"},
		{3,"11:40-13:00"},
		{4,"13:30-14:50"},
		{5,"15:00-16:20"},
		{6,"16:30-17:50"},
		{7,"18:00-19:20"}
	};

	map<int, std::string> weekDays = {
		{1,"Monday"},
		{2,"Tuesday"},
		{3,"Wednesday"},
		{4,"Thursday"},
		{5,"Friday"}
	};

	size_t _pairCount;
	size_t _removedPairs;

	string GeneratePair();

};