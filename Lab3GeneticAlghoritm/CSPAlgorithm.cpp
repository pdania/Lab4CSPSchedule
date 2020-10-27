#include"CSPAlgorithm.h"

using namespace std;

CSPAlgorithm::CSPAlgorithm(Config& config, size_t pairCount) :
	_config(config),
	_pairs(pairCount) {
}

void CSPAlgorithm::Init() {
	_index = vector<vector<Pair>>(weekDays.size() * pairTimes.size(), vector<Pair>(_config.GetNumberOfRooms()));

	for (auto& pair : _pairs) {
		pair = GeneratePair();
	}
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