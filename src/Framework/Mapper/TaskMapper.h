#pragma once
#include "../../Domain/Model/Task.h"

namespace Framework::Mapper {
	using namespace Domain::Model;

	class TaskMapper {
	public:
		static string map(const Task& task);
	};
}