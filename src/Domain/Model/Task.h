#pragma once
#include <iostream>

typedef std::string string;

namespace Domain::Model {
	class Task {
	public:
		int id;
		string title;

		Task(const int& id, const string& title);
	};
}
