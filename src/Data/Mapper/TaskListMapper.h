#pragma once

#include "TaskMapper.h"

namespace Data::Mapper {
	class TasksMapper {
	public:
		static std::vector<Task> map(json j);
	};
}
