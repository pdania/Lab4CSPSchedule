#include <string>

#pragma once

using namespace std;

class Course {
public:
	Course(int id, const string& name);

	inline int GetId() const { return _id; }

	inline const string& GetName() const { return _name; }

private:
	int _id;
	string _name;
};