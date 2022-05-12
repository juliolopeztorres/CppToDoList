#pragma once

#include "RemoveTodoUseCaseRepositoryInterface.h"

namespace Domain::RemoveTodoUseCase {
	class RemoveTodoUseCase {
	private:
		RemoveTodoUseCaseRepositoryInterface& repo;

	public:
		RemoveTodoUseCase(RemoveTodoUseCaseRepositoryInterface& repo);

		void remove(int id) const;
	};
}
