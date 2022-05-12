#pragma once
#include "EditTodoUseCaseRepositoryInterface.h"

namespace Domain::EditTodoUseCase {
	class EditTodoUseCase {
	private:
		EditTodoUseCaseRepositoryInterface& repo;
	public:
		EditTodoUseCase(EditTodoUseCaseRepositoryInterface& repo);

		void edit(const Task& task) const;
	};
}
