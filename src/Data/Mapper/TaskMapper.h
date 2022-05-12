#pragma once
#include <nlohmann/json.hpp>
#include "../../Domain/Model/Task.h"

namespace Data::Mapper {
	using json = nlohmann::json;
	using namespace Domain::Model;

	class TaskMapper {
	public:
		static Task map(json j);
		static json mapForSaving(Task task);
	};
}
