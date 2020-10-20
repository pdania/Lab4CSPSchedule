#include "Config.h"
#include "Professor.h"
#include "StudentsGroup.h"
#include "Course.h"
#include "Room.h"
#include "CourseClass.h"

Config Config::_instance;

Config::~Config()
{
	for (unordered_map<int, Professor*>::iterator it = _professors.begin(); it != _professors.end(); it++)
		delete (*it).second;

	for (unordered_map<int, StudentsGroup*>::iterator it = _studentGroups.begin(); it != _studentGroups.end(); it++)
		delete (*it).second;

	for (unordered_map<int, Course*>::iterator it = _courses.begin(); it != _courses.end(); it++)
		delete (*it).second;

	for (unordered_map<int, Room*>::iterator it = _rooms.begin(); it != _rooms.end(); it++)
		delete (*it).second;

	//for (list<CourseClass*>::iterator it = _courseClasses.begin(); it != _courseClasses.end(); it++)
	//	delete* it;
}

void Config::ParseFile(char* fileName)
{
	// clear previously parsed objects
	_professors.clear();
	_studentGroups.clear();
	_courses.clear();
	_rooms.clear();
	//_courseClasses.clear();

	Room::RestartIDs();

	// open file
	ifstream input(fileName);

	string line;
	while (input.is_open() && !input.eof())
	{
		// get lines until start of new object is not found
		getline(input, line);
		TrimString(line);

		// get type of object, parse obect and store it

		if (line.compare("#prof") == 0)
		{
			Professor* p = ParseProfessor(input);
			if (p)
				_professors.insert(pair<int, Professor*>(p->GetId(), p));
		}
		else if (line.compare("#group") == 0)
		{
			StudentsGroup* g = ParseStudentsGroup(input);
			if (g)
				_studentGroups.insert(pair<int, StudentsGroup*>(g->GetId(), g));
		}
		else if (line.compare("#course") == 0)
		{
			Course* c = ParseCourse(input);
			if (c)
				_courses.insert(pair<int, Course*>(c->GetId(), c));
		}
		else if (line.compare("#room") == 0)
		{
			Room* r = ParseRoom(input);
			if (r)
				_rooms.insert(pair<int, Room*>(r->GetId(), r));
		}
		/*else if (line.compare("#class") == 0)
		{
			CourseClass* c = ParseCourseClass(input);
			if (c)
				_courseClasses.push_back(c);
		}*/
	}

	input.close();

	_isEmpty = false;
}

Professor* Config::ParseProfessor(ifstream& file)
{
	int id = 0;
	string name;

	while (!file.eof())
	{
		string key, value;

		// get key - value pair
		if (!GetConfigBlockLine(file, key, value))
			break;

		// get value of key
		if (key.compare("id") == 0)
			id = atoi(value.c_str());
		else if (key.compare("name") == 0)
			name = value;
	}

	// make object and return pointer to it
	return id == 0 ? NULL : new Professor(id, name);
}

StudentsGroup* Config::ParseStudentsGroup(ifstream& file)
{
	int id = 0, number = 0;
	string name;

	while (!file.eof())
	{
		string key, value;

		// get key - value pair
		if (!GetConfigBlockLine(file, key, value))
			break;

		// get value of key
		if (key.compare("id") == 0)
			id = atoi(value.c_str());
		else if (key.compare("name") == 0)
			name = value;
		else if (key.compare("size") == 0)
			number = atoi(value.c_str());
	}

	// make object and return pointer to it
	return id == 0 ? NULL : new StudentsGroup(id, name, number);
}

Course* Config::ParseCourse(ifstream& file)
{
	int id = 0;
	string name;
	bool lab;

	while (!file.eof())
	{
		string key, value;

		// get key - value pair
		if (!GetConfigBlockLine(file, key, value))
			break;

		// get value of key
		if (key.compare("id") == 0)
			id = atoi(value.c_str());
		else if (key.compare("name") == 0)
			name = value;
		else if (key.compare("requiresLab") == 0)
			lab = value.compare("true") == 0;
	}

	// make object and return pointer to it
	return id == 0 ? NULL : new Course(id, name, lab);
}

//Practice* Config::ParsePractice(ifstream& file)
//{
//	int id = 0;
//	string name;
//
//	while (!file.eof())
//	{
//		string key, value;
//
//		// get key - value pair
//		if (!GetConfigBlockLine(file, key, value))
//			break;
//
//		// get value of key
//		if (key.compare("id") == 0)
//			id = atoi(value.c_str());
//		else if (key.compare("name") == 0)
//			name = value;
//	}
//
//	// make object and return pointer to it
//	return id == 0 ? NULL : new Practice(id, name);
//}

Room* Config::ParseRoom(ifstream& file)
{
	int number = 0;
	bool lab = false;
	string name;

	while (!file.eof())
	{
		string key, value;

		// get key - value pair
		if (!GetConfigBlockLine(file, key, value))
			break;

		// get value of key
		if (key.compare("name") == 0)
			name = value;
		else if (key.compare("lab") == 0)
			lab = value.compare("true") == 0;
		else if (key.compare("size") == 0)
			number = atoi(value.c_str());
	}

	// make object and return pointer to it
	return number == 0 ? NULL : new Room(name, lab, number);
}

//CourseClass* Config::ParseCourseClass(ifstream& file)
//{
//	int pid = 0, cid = 0,prid = 0, dur = 1;
//	bool lab = false;
//
//	list<StudentsGroup*> groups;
//
//	while (!file.eof())
//	{
//		string key, value;
//
//		// get key - value pair
//		if (!GetConfigBlockLine(file, key, value))
//			break;
//
//		// get value of key
//		if (key.compare("professor") == 0)
//			pid = atoi(value.c_str());
//		else if (key.compare("course") == 0)
//			cid = atoi(value.c_str());
//		else if (key.compare("practice") == 0)
//			prid = atoi(value.c_str());
//		else if (key.compare("lab") == 0)
//			lab = value.compare("true") == 0;
//		else if (key.compare("duration") == 0)
//			dur = atoi(value.c_str());
//		else if (key.compare("group") == 0)
//		{
//			StudentsGroup* g = GetStudentsGroupById(atoi(value.c_str()));
//			if (g)
//				groups.push_back(g);
//		}
//	}
//
//	// get professor who teaches class and course to which this class belongs
//	Professor* p = GetProfessorById(pid);
//	Course* c = GetCourseById(cid);
//	//Practice* pr = GetPracticeById(prid);
//
//	// does professor and class exists
//	if (!c || !p)
//		return NULL;
//
//	// make object and return pointer to it
//	if (!pr) {
//		CourseClass* cc = new CourseClass(p, c, pr, groups, lab, dur);
//		return cc;
//	}
//	else 
//	{
//		CourseClass* cc = new CourseClass(p, c, groups, lab, dur);
//		return cc;
//	}
//	
//}

bool Config::GetConfigBlockLine(ifstream& file, string& key, string& value)
{
	string line;

	// end of file
	while (!file.eof())
	{
		// read line from config file
		getline(file, line);
		TrimString(line);

		// end of object's data 
		if (line.compare("#end") == 0)
			return false;

		size_t p = line.find('=');
		if (p != string::npos)
		{
			// key
			key = line.substr(0, p);
			TrimString(key);

			// value
			value = line.substr(p + 1, line.length());
			TrimString(value);

			// key - value pair read successfully
			return true;
		}
	}

	// error
	return false;
}

string& Config::TrimString(string& str)
{
	string::iterator it;
	for (it = str.begin(); it != str.end() && isspace(*it); it++)
		;
	str.erase(str.begin(), it);

	string::reverse_iterator rit;
	for (rit = str.rbegin(); rit != str.rend() && isspace(*rit); rit++)
		;
	str.erase(str.begin() + (str.rend() - rit), str.end());

	return str;
}