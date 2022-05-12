#pragma once

#include "../Model/Task.h"

namespace Domain::CreateTodoUseCase {
	using namespace Domain::Model;

	class CreateTodoUseCaseRepositoryInterface {
	public:
		virtual void create(const Task& task) = 0;
	};
}
