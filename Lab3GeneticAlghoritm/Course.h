#include <string>

#pragma once

using namespace std;

class Course {
public:
	Course(int id, const string& name, bool requiresLab);

	inline int GetId() const { return _id; }

	inline const string& GetName() const { return _name; }

	inline const bool IsRequiresLab() const { return _requiresLab;  }

private:
	int _id;
	string _name;
	bool _requiresLab;
};