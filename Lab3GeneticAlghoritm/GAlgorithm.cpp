#include "GAlgorithm.h"
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <set>
#include <string_view>
#include <algorithm>

GAlgorithm::GAlgorithm(Config& config, size_t crossoverProbability, size_t mutationProbability) :_config(config),
_crossoverProbability(crossoverProbability),
_mutationProbability(mutationProbability),
_removedPairs(0){
}


void GAlgorithm::ProcessAlgorithm() {
	while (CheckPairs) {
		AddPairs();
		Cross();
		Mutate();
	}
}

void GAlgorithm::AddPairs() {
	for (int i = 0; i < _removedPairs; ++i) {
		_population.push_back(GeneratePair());
		cout << "New pair added to population" << endl;
	}
	_removedPairs = 0;
}

void GAlgorithm::Init() {
	for (int i = 0; i < 8; ++i) {
		_population.push_back(GeneratePair());
	}
}

void GAlgorithm::Cross() {
	srand((unsigned)time(NULL));

	if (rand() % 100 > _crossoverProbability)
		return;
	set<string*> used_parents;
	for (int i = 0; i < _population.size() / 2 + 1; ++i) {
		string& first_parent = _population[rand() % _population.size()];
		while (used_parents.count(&first_parent) > 0) {
			first_parent = _population[rand() % _population.size()];
		}
		string& second_parent = _population[rand() % _population.size()];
		while (used_parents.count(&second_parent) > 0) {
			second_parent = _population[rand() % _population.size()];
		}
		used_parents.insert(&first_parent);
		used_parents.insert(&second_parent);
		int div_index = rand() % min(first_parent.size(), second_parent.size());
		swap_ranges(begin(first_parent) + div_index, end(first_parent), begin(second_parent) + div_index);
	}
}

void GAlgorithm::Mutate() {
	srand((unsigned)time(NULL));

	if (rand() % 100 > _mutationProbability)
		return;

	for (int i = 0; i < _population.size() / 2; ++i) {
		string& person_for_mutation = _population[rand() % _population.size()];
		int mutation_type = rand() % 9;
		switch (static_cast<MutationType>(mutation_type))
		{
		case MutationType::ChangeDay:
		{
			string pair = _population.at(i);
			int newDay = rand() % WORK_DAYS_NUMBER;
			pair.replace(0, 1, to_string(newDay));
			break;
		}
		case MutationType::ChangePair:
		{
			string pair = _population.at(i);
			int newPairTime = rand() % PAIRS_NUMBER_A_DAY;
			pair.replace(1, 1, to_string(newPairTime));
			break;
		}
		case MutationType::ChangeClassrom:
		{
			string pair = _population.at(i);
			int newRoomNumber = rand() % _config.GetNumberOfRooms();
			ostringstream out;
			out << std::setfill('0') << std::setw(2) << newRoomNumber;
			pair.replace(2, 2, out.str());
			break;
		}
		case MutationType::ChangeCourse:
		{
			string pair = _population.at(i);
			int newCourse = rand() % _config.GetNumberOfCourses();
			ostringstream out;
			out << std::setfill('0') << std::setw(2) << newCourse;
			pair.replace(4, 2, out.str());
			break;
		}
		case MutationType::ChangeProfessor:
		{
			string pair = _population.at(i);
			int newProf = rand() % _config.GetNumberOfProfessors();
			ostringstream out;
			out << std::setfill('0') << std::setw(2) << newProf;
			pair.replace(6, 2, out.str());
			break;
		}
		case MutationType::ChangeLecturePractice:
		{
			string pair = _population.at(i);
			int isLecture = rand() % 2;
			pair.replace(8, 1, to_string(isLecture));
			break;
		}
		case MutationType::ChangeGroup:
		{
			string pair = _population.at(i);
			int newGroup = rand() % _config.GetNumberOfStudentGroups();
			ostringstream out;
			out << std::setfill('0') << std::setw(2) << newGroup;
			pair.replace(9, 2, out.str());
			break;
		}
		case MutationType::AddPair:
			_population.push_back(GeneratePair());
			break;

		case MutationType::RemovePair:
			int index_for_remove = rand() % _population.size();
			_population.erase(begin(_population) + index_for_remove);
			break;

		default:
			throw out_of_range(mutation_type + " is more than enum elements count.");
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
		if (_config.GetCourseById(course)->IsRequiresLab() != _config.GetRoomById(classroom)->IsLab()) {
			_population.erase(_population.begin() + i);
			cout << "Pair number "<< i <<" removed from population" << endl;
			_removedPairs++;
			continue;
		}
		if (_config.GetStudentsGroupById(group)->GetNumberOfStudents() > _config.GetRoomById(classroom)->GetNumberOfSeats()) {
			_population.erase(_population.begin() + i);
			cout << "Pair number " << i << " removed from population" << endl;
			_removedPairs++;
			continue;
		}
	}
	/* TODO
	* Add check between pairs (overlap or not)
	*/
	if (_removedPairs)
		return true;
	return false;
}

string GAlgorithm::GeneratePair() {
	srand((unsigned)time(NULL));

	int day_num = rand() % WORK_DAYS_NUMBER;
	int pair_num = rand() % PAIRS_NUMBER_A_DAY;
	int classrooom_id = rand() % _config.GetNumberOfRooms();
	int course_id = rand() % _config.GetNumberOfCourses();
	int professor_id = rand() % _config.GetNumberOfProfessors();
	int is_lection = rand() % 2;
	int group_id = _config.GetNumberOfStudentGroups();

	ostringstream out;
	out << std::setfill('0') << std::setw(1) << day_num << std::setw(1) <<
		pair_num << std::setw(2) << classrooom_id << std::setw(2) << course_id <<
		std::setw(2) << professor_id << std::setw(1) << is_lection << std::setw(2) << group_id;
	return out.str();
}