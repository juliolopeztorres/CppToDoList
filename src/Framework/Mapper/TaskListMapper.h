#pragma once
#include <vector>
#include "TaskMapper.h"

namespace Framework::Mapper {
	using namespace Domain::Model;

	class TasksMapper {
	public:
		static string map(const std::vector<Task>& tasks);
	};
}

