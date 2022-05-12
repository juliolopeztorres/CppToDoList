#pragma once
#include "TaskListMapper.h"

using namespace Framework::Mapper;

string TasksMapper::map(const std::vector<Task>& tasks) {
	string output = "";

	int tasksNumber = tasks.size();
	int tasksMappedNumber = 0;
	for (Task task : tasks) {
		output += TaskMapper::map(task);
		
		if (++tasksMappedNumber != tasksNumber) {
			output += "\n";
		}
	}

	if (output.empty()) {
		output = "There is no tasks stored yet!\n";
	}

	return output;
}