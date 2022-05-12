#pragma once

namespace Domain::RemoveTodoUseCase {
	class RemoveTodoUseCaseRepositoryInterface {
	public:
		virtual void remove(const int& id) = 0;
	};
}
