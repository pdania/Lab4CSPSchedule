
#include <list>
#include <hash_map>
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

class Config
{

private:

	static Config _instance;

public:

	inline static Config& GetInstance() { return _instance; }

private:

	hash_map<int, Professor*> _professors;

	hash_map<int, StudentsGroup*> _studentGroups;

	hash_map<int, Course*> _courses;

	hash_map<int, Room*> _rooms;

	list<CourseClass*> _courseClasses;

	bool _isEmpty;

public:

	Config() : _isEmpty(true) { }

	~Config();

	void ParseFile(char* fileName);

	inline Professor* GetProfessorById(int id)
	{
		hash_map<int, Professor*>::iterator it = _professors.find(id);
		return it != _professors.end() ? (*it).second : NULL;
	}

	inline int GetNumberOfProfessors() const { return (int)_professors.size(); }

	inline StudentsGroup* GetStudentsGroupById(int id)
	{
		hash_map<int, StudentsGroup*>::iterator it = _studentGroups.find(id);
		return it != _studentGroups.end() ? (*it).second : NULL;
	}

	inline int GetNumberOfStudentGroups() const { return (int)_studentGroups.size(); }

	inline Course* GetCourseById(int id)
	{
		hash_map<int, Course*>::iterator it = _courses.find(id);
		return it != _courses.end() ? (*it).second : NULL;
	}

	inline int GetNumberOfCourses() const { return (int)_courses.size(); }

	inline Room* GetRoomById(int id)
	{
		hash_map<int, Room*>::iterator it = _rooms.find(id);
		return it != _rooms.end() ? (*it).second : NULL;
	}

	inline int GetNumberOfRooms() const { return (int)_rooms.size(); }

	inline const list<CourseClass*>& GetCourseClasses() const { return _courseClasses; }

	inline int GetNumberOfCourseClasses() const { return (int)_courseClasses.size(); }

	inline bool IsEmpty() const { return _isEmpty; }

private:
	Professor* ParseProfessor(ifstream& file);

	StudentsGroup* ParseStudentsGroup(ifstream& file);

	Course* ParseCourse(ifstream& file);

	Room* ParseRoom(ifstream& file);

	CourseClass* ParseCourseClass(ifstream& file);

	bool GetConfigBlockLine(ifstream& file, string& key, string& value);

	string& TrimString(string& str);

};