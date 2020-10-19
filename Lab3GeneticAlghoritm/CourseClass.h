#include <list>
#include "Professor.h"
#include "StudentsGroup.h"
#include "Course.h"
#include"Practice.h"

#pragma once

using namespace std;

class CourseClass {
public:
	CourseClass(Professor* professor, Course* course, const list<StudentsGroup*>& groups,
		bool requiresLab, int duration);
	CourseClass(Professor* professor, Course* course, Practice* practice, const list<StudentsGroup*>& groups,
		bool requiresLab, int duration);

	~CourseClass();

	bool GroupsOverlap(const CourseClass& c) const;

	inline bool ProfessorOverlaps(const CourseClass& c) const { return *_professor == *c._professor; }

	inline const Professor& GetProfessor() const { return *_professor; }

	inline const Course& GetCourse() const { return *_course; }

	inline const list<StudentsGroup*>& GetGroups() const { return _groups; }

	inline int GetNumberOfSeats() const { return _numberOfSeats; }

	inline bool IsLabRequired() const { return _requiresLab; }

	inline int GetDuration() const { return _duration; }

private:
	Professor* _professor;
	Course* _course;
	Practice* _practice;
	list<StudentsGroup*> _groups;
	int _numberOfSeats;
	bool _requiresLab;
	int _duration;
};
