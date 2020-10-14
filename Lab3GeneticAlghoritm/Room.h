#include <string>

#pragma once

using namespace std;

class Room {
public:
	Room(const string& name, bool lab, int numberOfSeats);

	inline int GetId() const { return _id; }

	inline const string& GetName() const { return _name; }

	inline bool IsLab() const { return _lab; }

	inline int GetNumberOfSeats() const { return _numberOfSeats; }

	static inline void RestartIDs() { _nextRoomId = 0; }

private:
	static int _nextRoomId;

	int _id;
	string _name;
	bool _lab;
	int _numberOfSeats;
};