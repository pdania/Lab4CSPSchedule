#pragma once

#include "Config.h"
#include "Course.h"
#include "Room.h"
#include "StudentsGroup.h"
#include "Professor.h"
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iomanip>
#include <iostream>
#include <algorithm>

struct Pair {
	Professor* professor;
	Course* course;
	StudentsGroup* group;
	bool isLection;
};

class CSPAlgorithm {
public:
	typedef std::vector<std::vector<Pair>> IndexType;

public:
	CSPAlgorithm(Config& config, size_t pairCount);

	void Init();

	void ProcessAlgorithm();

	inline const IndexType& Index() const {
		return _index;
	}
	inline const std::map<int, std::string>& PairTimes() const {
		return _pairTimes;
	}
	inline const std::map<int, std::string>& WeekDays() const {
		return _weekDays;
	}

private:
	IndexType _index;
	std::vector<Pair> _pairs;

	std::map<int, int> _professors_frequency;
	std::map<int, int> _groups_frequency;
	std::vector<std::set<int>> _used_professors;
	std::vector<std::set<int>> _used_groups;

	Config& _config;

	std::map<int, std::string> _pairTimes = {
		{1,"8:00-9:50"},
		{2,"10:00-11:20"},
		{3,"11:40-13:00"},
		{4,"13:30-14:50"},
		{5,"15:00-16:20"},
		{6,"16:30-17:50"},
		{7,"18:00-19:20"}
	};

	std::map<int, std::string> _weekDays = {
		{1,"Monday"},
		{2,"Tuesday"},
		{3,"Wednesday"},
		{4,"Thursday"},
		{5,"Friday"}
	};

	Pair GeneratePair();
};