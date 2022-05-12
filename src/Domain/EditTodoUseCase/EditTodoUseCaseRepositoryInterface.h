#pragma once
#include "../Model/Task.h"

namespace Domain::EditTodoUseCase {
	using namespace Domain::Model;

	class EditTodoUseCaseRepositoryInterface {
	public:
		virtual void edit(const Task& task) = 0;
	};
}
