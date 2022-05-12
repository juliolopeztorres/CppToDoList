#pragma once
#include <vector>

#include "../Model/Task.h"

namespace Domain::GetTodosUseCase {
	using namespace Domain::Model;

	class GetTodosUseCaseRepositoryInterface {
	public:
		virtual std::vector<Task> get() = 0;
	};
}
