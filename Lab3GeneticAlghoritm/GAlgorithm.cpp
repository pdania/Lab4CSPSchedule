#include "GAlgorithm.h"
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <set>
#include <string_view>
#include <algorithm>

GAlgorithm::GAlgorithm(Config& config, size_t crossoverProbability, size_t mutationProbability, size_t pairCount) :
	_config(config),
	_crossoverProbability(crossoverProbability),
	_pairCount(pairCount),
	_mutationProbability(mutationProbability),
	_removedPairs(0) {
}


void GAlgorithm::ProcessAlgorithm() {
	Init();

	while (CheckPairs()) {
		AddPairs();
		Cross();
		Mutate();
	}

	PrintSchedule();
}

void GAlgorithm::AddPairs() {
	for (int i = 0; i < _removedPairs; ++i) {
		_population.push_back(GeneratePair());
		cout << "New Person added to population" << endl;
	}
	_removedPairs = 0;
}

void GAlgorithm::Init() {
	for (int i = 0; i < _pairCount; ++i) {
		_population.push_back(GeneratePair());
	}
}

void GAlgorithm::Cross() {
	if (rand() % 100 > _crossoverProbability)
		return;
	set<int> used_parent_numbers;
	for (int i = 0; i < _population.size() / 2; ++i) {
		int first_parent_num = rand() % _population.size();
		while (used_parent_numbers.count(first_parent_num) > 0) {
			first_parent_num = rand() % _population.size();
		}
		int second_parent_num = rand() % _population.size();
		while (used_parent_numbers.count(second_parent_num) > 0) {
			second_parent_num = rand() % _population.size();
		}
		used_parent_numbers.insert(first_parent_num);
		used_parent_numbers.insert(second_parent_num);

		cout << "Crossed persons " << first_parent_num << " and " << second_parent_num << endl;

		string& first_parent = _population[first_parent_num];
		string& second_parent = _population[second_parent_num];
		int div_index = rand() % min(first_parent.size(), second_parent.size());
		swap_ranges(begin(first_parent) + div_index, end(first_parent), begin(second_parent) + div_index);
	}
}

void GAlgorithm::Mutate() {
	if (rand() % 100 > _mutationProbability)
		return;

	for (int i = 0; i < _population.size() / 2; ++i) {
		int person_id_for_mutation = rand() % _population.size();
		cout << "Mutated person with id "<< person_id_for_mutation << endl;

		string& person_for_mutation = _population[person_id_for_mutation];
		int mutation_type = rand() % 9;
		switch (static_cast<MutationType>(mutation_type))
		{
		case MutationType::ChangeDay:
		{
			int newDay = rand() % WORK_DAYS_NUMBER;
			person_for_mutation.replace(0, 1, to_string(newDay));
			break;
		}
		case MutationType::ChangePair:
		{
			int newPairTime = rand() % PAIRS_NUMBER_A_DAY;
			person_for_mutation.replace(1, 1, to_string(newPairTime));
			break;
		}
		case MutationType::ChangeClassrom:
		{
			int newRoomNumber = rand() % _config.GetNumberOfRooms();
			ostringstream out;
			out << std::setfill('0') << std::setw(2) << newRoomNumber;
			person_for_mutation.replace(2, 2, out.str());
			break;
		}
		case MutationType::ChangeCourse:
		{
			int newCourse = rand() % _config.GetNumberOfCourses();
			ostringstream out;
			out << std::setfill('0') << std::setw(2) << newCourse;
			person_for_mutation.replace(4, 2, out.str());
			break;
		}
		case MutationType::ChangeProfessor:
		{
			int newProf = rand() % _config.GetNumberOfProfessors();
			ostringstream out;
			out << std::setfill('0') << std::setw(2) << newProf;
			person_for_mutation.replace(6, 2, out.str());
			break;
		}
		case MutationType::ChangeLecturePractice:
		{
			int isLecture = rand() % 2;
			person_for_mutation.replace(8, 1, to_string(isLecture));
			break;
		}
		case MutationType::ChangeGroup:
		{
			int newGroup = rand() % _config.GetNumberOfStudentGroups();
			ostringstream out;
			out << std::setfill('0') << std::setw(2) << newGroup;
			person_for_mutation.replace(9, 2, out.str());
			break;
		}
		case MutationType::AddPair:
		{
			_population.push_back(GeneratePair());
			break;
		}
		case MutationType::RemovePair:
		{
			int index_for_remove = rand() % _population.size();
			_population.erase(begin(_population) + index_for_remove);
			break;
		}
		default:
		{
			throw out_of_range(mutation_type + " is more than enum elements number.");
		}
		}
	}
}

bool GAlgorithm::CheckPairs() {
	for (size_t i = 0; i < _population.size(); i++)
	{
		string pair = _population.at(i);
		int course = stoi(pair.substr(4, 2));
		int classroom = stoi(pair.substr(2, 2));
		int group = stoi(pair.substr(9, 2));

		if (_config.GetCourseById(course)->IsRequiresLab() && !(_config.GetRoomById(classroom)->IsLab())) {
			_population.erase(_population.begin() + i);
			cout << "Person number " << i << " removed from population, because a room is not intended for laboratory works." << endl;
			_removedPairs++;
			continue;
		}

		if (_config.GetStudentsGroupById(group)->GetNumberOfStudents() > _config.GetRoomById(classroom)->GetNumberOfSeats()) {
			_population.erase(_population.begin() + i);
			cout << "Person number " << i << " removed from population, because number of seats less than number of students." << endl;
			_removedPairs++;
			continue;
		}
	}

	/* TODO
	* Add check between pairs (overlap or not)
	*/

	return _removedPairs > 0;
}

void GAlgorithm::PrintSchedule() {

		for (size_t j = 0; j < WORK_DAYS_NUMBER; j++)
		{
			cout << weekDays[j + 1] << ":" << endl;

			for (size_t k = 0; k < PAIRS_NUMBER_A_DAY; k++)
			{
				for (size_t i = 0; i < _population.size(); i++)
				{
					string pair = _population.at(i);
					if ((j != stoi(pair.substr(0, 1))) || (k != stoi(pair.substr(1, 1))))
						continue;

					string pairType = (stoi(pair.substr(8, 1))) ? "Lecture" : "Practice";
					string roomName = _config.GetRoomById(stoi(pair.substr(2, 2)))->GetName();
					string courseName = _config.GetCourseById(stoi(pair.substr(4, 2)))->GetName();
					string profName = _config.GetProfessorById(stoi(pair.substr(6, 2)))->GetName();
					string groupName = _config.GetStudentsGroupById(stoi(pair.substr(9, 2)))->GetName();
					cout << pairTimes[k + 1] << endl;
					cout << "	PairType: " << pairType << endl;
					cout << "	Professor: " << profName << endl;
					cout << "	Course: " << courseName << endl;
					cout << "	ClassRoom: " << roomName << endl;
					cout << "	Group: " << groupName << endl;
					cout << "-------------------------" << endl;
				}
			}

			cout << "***************************************************" << endl;
		}

}


string GAlgorithm::GeneratePair() {
	int day_num = rand() % WORK_DAYS_NUMBER;
	int pair_num = rand() % PAIRS_NUMBER_A_DAY;
	int classrooom_id = rand() % _config.GetNumberOfRooms();
	int course_id = rand() % _config.GetNumberOfCourses();
	int professor_id = rand() % _config.GetNumberOfProfessors();
	int is_lection = rand() % 2;
	int group_id = rand() % _config.GetNumberOfStudentGroups();

	ostringstream out;
	out << std::setfill('0') << std::setw(1) << day_num << std::setw(1) <<
		pair_num << std::setw(2) << classrooom_id << std::setw(2) << course_id <<
		std::setw(2) << professor_id << std::setw(1) << is_lection << std::setw(2) << group_id;
	return out.str();
}