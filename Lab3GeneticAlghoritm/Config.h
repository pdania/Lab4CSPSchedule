#include <list>
#include <unordered_map>
#include <fstream>
#include <string>

#pragma once

using namespace std;
using namespace stdext;

class Professor;
class StudentsGroup;
class Course;
class Room;
class CourseClass;

class Config {
public:
	inline static Config& GetInstance() { return _instance; }

private:
	static Config _instance;

public:
	Config() : _isEmpty(true) { }

	~Config();

	void ParseFile(char* fileName);

	inline Professor* GetProfessorById(int id) {
		unordered_map<int, Professor*>::iterator it = _professors.find(id);
		return it != _professors.end() ? (*it).second : NULL;
	}

	inline int GetNumberOfProfessors() const { return (int)_professors.size(); }

	inline StudentsGroup* GetStudentsGroupById(int id) {
		unordered_map<int, StudentsGroup*>::iterator it = _studentGroups.find(id);
		return it != _studentGroups.end() ? (*it).second : NULL;
	}

	inline int GetNumberOfStudentGroups() const { return (int)_studentGroups.size(); }

	inline Course* GetCourseById(int id) {
		unordered_map<int, Course*>::iterator it = _courses.find(id);
		return it != _courses.end() ? (*it).second : NULL;
	}

	inline int GetNumberOfCourses() const { return (int)_courses.size(); }

	inline Room* GetRoomById(int id) {
		unordered_map<int, Room*>::iterator it = _rooms.find(id);
		return it != _rooms.end() ? (*it).second : NULL;
	}

	inline int GetNumberOfRooms() const { return (int)_rooms.size(); }

	inline const list<CourseClass*>& GetCourseClasses() const { return _courseClasses; }

	inline int GetNumberOfCourseClasses() const { return (int)_courseClasses.size(); }

	inline bool IsEmpty() const { return _isEmpty; }

private:
	unordered_map<int, Professor*> _professors;
	unordered_map<int, StudentsGroup*> _studentGroups;
	unordered_map<int, Course*> _courses;
	unordered_map<int, Room*> _rooms;
	list<CourseClass*> _courseClasses;
	bool _isEmpty;

private:
	Professor* ParseProfessor(ifstream& file);
	StudentsGroup* ParseStudentsGroup(ifstream& file);
	Course* ParseCourse(ifstream& file);
	Room* ParseRoom(ifstream& file);
	CourseClass* ParseCourseClass(ifstream& file);

	bool GetConfigBlockLine(ifstream& file, string& key, string& value);

	string& TrimString(string& str);
};