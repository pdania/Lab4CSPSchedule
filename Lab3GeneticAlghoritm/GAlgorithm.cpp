#include "GAlgorithm.h"
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <set>
#include <string_view>
#include <algorithm>

using namespace std;

GAlgorithm::GAlgorithm(Config& config) :_config(config) {
}

void GAlgorithm::Init() {
	for (int i = 0; i < 8; ++i) {
		_population.push_back(GeneratePair());
	}
}

void GAlgorithm::Cross() {
	srand((unsigned)time(NULL));

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

	for (int i = 0; i < _population.size() / 2; ++i) {
		string& person_for_mutation = _population[rand() % _population.size()];
		int mutation_type = rand() % 9;
		switch (static_cast<MutationType>(mutation_type))
		{
		case MutationType::ChangeDay:
			break;
		case MutationType::ChangePair:
			break;
		case MutationType::ChangeClassrom:
			break;
		case MutationType::ChangeCourse:
			break;
		case MutationType::ChangeProfessor:
			break;
		case MutationType::ChangeLecturePractice:
			break;
		case MutationType::ChangeGroup:
			break;
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







string GAlgorithm::GeneratePair() {
	srand((unsigned)time(NULL));

	int day_num = rand() % WORK_DAYS_NUMBER;
	int pair_num = rand() % PAIRS_NUMBER_A_DAY;
	int classrooom_id = rand() % _config.GetNumberOfRooms();
	int course_id = rand() % _config.GetNumberOfRooms();
	int professor_id = rand() % _config.GetNumberOfProfessors();
	int is_lection = rand() % 2;
	int group_id = _config.GetNumberOfStudentGroups();

	ostringstream out;
	out << day_num << pair_num << classrooom_id << course_id << professor_id << is_lection << group_id;
	return out.str();
}