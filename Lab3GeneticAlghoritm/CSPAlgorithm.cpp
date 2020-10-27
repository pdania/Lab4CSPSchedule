#include"CSPAlgorithm.h"

using namespace std;

CSPAlgorithm::CSPAlgorithm(Config& config, size_t pairCount) :
	_config(config),
	_pairs(pairCount) {
}

void CSPAlgorithm::Init() {
	_index = vector<vector<Pair>>(_weekDays.size() * _pairTimes.size(), vector<Pair>(_config.GetNumberOfRooms()));

	for (auto& pair : _pairs) {
		pair = GeneratePair();
	}
}

void CSPAlgorithm::ProcessAlgorithm() {
	sort(begin(_pairs), end(_pairs), [](Pair& p1, Pair& p2) {
		return p1.isLection < p2.isLection;
		});
}



Pair CSPAlgorithm::GeneratePair() {
	int professor_id = rand() % _config.GetNumberOfProfessors();
	int course_id = rand() % _config.GetNumberOfCourses();
	int group_id = rand() % _config.GetNumberOfStudentGroups();
	bool is_lection = rand() % 2;

	return Pair{
		_config.GetProfessorById(professor_id),
		_config.GetCourseById(course_id),
		_config.GetStudentsGroupById(group_id),
		is_lection,
	};
}