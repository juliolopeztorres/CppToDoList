#pragma once
#include "TaskMapper.h"
#include "string"

using namespace Framework::Mapper;

string TaskMapper::map(const Task& task) {
	return "\tTask ID: " + std::to_string(task.id) + "\n" + \
		"\tTitle: " + task.title + "\n";
};