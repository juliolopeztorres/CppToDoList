#pragma once

#include "CreateTodoUseCaseRepositoryInterface.h"

namespace Domain::CreateTodoUseCase {
	class CreateTodoUseCase {
	private:
		CreateTodoUseCaseRepositoryInterface& repo;

	public:
		CreateTodoUseCase(CreateTodoUseCaseRepositoryInterface& repo);

		void create(const Task& task) const;
	};
}
