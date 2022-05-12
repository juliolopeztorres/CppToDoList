#pragma once
#include "TaskMapper.h"

using namespace Data::Mapper;

Task TaskMapper::map(json j)
{
	return Task(
		j["id"].get<int>(),
		j["title"].get<string>()
	);
}

json TaskMapper::mapForSaving(Task task) {
	json j;

	j["id"] = task.id;
	j["title"] = task.title;

	return j;
}