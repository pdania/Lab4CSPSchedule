#include"CSPAlgorithm.h"

using namespace std;

CSPAlgorithm::CSPAlgorithm(Config& config, size_t pairCount) :
	_config(config),
	_pairs(pairCount) {
}

void CSPAlgorithm::Init() {
	_index = vector<vector<Pair>>(_weekDays.size() * _pairTimes.size(), vector<Pair>(_config.GetNumberOfRooms()));
	_used_professors.resize(_index.size());
	_used_groups.resize(_index.size());

	for (auto& pair : _pairs) {
		pair = GeneratePair();
	}
}

void CSPAlgorithm::ProcessAlgorithm() {
	// Sort all pairs by freeqquency of professors and groups
	sort(begin(_pairs), end(_pairs), [&](Pair& p1, Pair& p2) {
		return
			(_professors_frequency[p1.professor->GetId()] > _professors_frequency[p2.professor->GetId()] &&
				_groups_frequency[p1.group->GetId()] > _groups_frequency[p2.group->GetId()]) ||
			(_professors_frequency[p1.professor->GetId()] > _professors_frequency[p2.professor->GetId()] &&
				_groups_frequency[p1.group->GetId()] == _groups_frequency[p2.group->GetId()]) ||
			(_professors_frequency[p1.professor->GetId()] == _professors_frequency[p2.professor->GetId()] &&
				_groups_frequency[p1.group->GetId()] > _groups_frequency[p2.group->GetId()]);
		});

	for (auto& pair : _pairs) {
		int x = rand() % _index.size();
		int y = rand() % _index[0].size();

		// Check for valid 'place' in shedule for current pair
		while (_used_professors[x].count(pair.professor->GetId()) > 0 ||
			_used_groups[x].count(pair.group->GetId()) > 0 ||
			(pair.isLection && _config.GetRoomById(y)->IsLab())) {
			x = rand() % _index.size();
			y = rand() % _index[0].size();
		}

		// Mark that group and proffesor are used at this time.
		_used_professors[x].insert(pair.professor->GetId());
		_used_groups[x].insert(pair.group->GetId());

		// Add current pair to index
		_index[x][y] = pair;
	}
}



Pair CSPAlgorithm::GeneratePair() {
	int professor_id = rand() % _config.GetNumberOfProfessors();
	int course_id = rand() % _config.GetNumberOfCourses();
	int group_id = rand() % _config.GetNumberOfStudentGroups();
	bool is_lection = rand() % 2;

	_professors_frequency[professor_id]++;
	_groups_frequency[group_id]++;

	return Pair{
		_config.GetProfessorById(professor_id),
		_config.GetCourseById(course_id),
		_config.GetStudentsGroupById(group_id),
		is_lection,
	};
}