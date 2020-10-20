#pragma once
#include <list>
#include <string>


using namespace std;
class Professor
{

private:

	int _id;

	string _name;

public:

	Professor(int id, const string& name);
	
	~Professor();

	inline int GetId() const { return _id; }

	inline const string& GetName() const { return _name; }

	inline bool operator ==(const Professor& rhs) const { return _id == rhs._id; }

};