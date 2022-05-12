#pragma once
#include "TaskListMapper.h"

using namespace Data::Mapper;

std::vector<Task> TasksMapper::map(json j) {
	std::vector<Task> vector;

	for (json element : j)
	{
		vector.push_back(
			TaskMapper::map(element)
		);
	}

	return vector;
}