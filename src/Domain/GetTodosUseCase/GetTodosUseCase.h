#pragma once

#include "GetTodosUseCaseRepositoryInterface.h"

namespace Domain::GetTodosUseCase {
	class GetTodosUseCase {
	private:
		GetTodosUseCaseRepositoryInterface& repo;

	public:
		GetTodosUseCase(GetTodosUseCaseRepositoryInterface& repo);

		std::vector<Task> get() const;
	};
}
