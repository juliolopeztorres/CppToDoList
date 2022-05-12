#pragma once
#include "GetTodosUseCase.h"

using namespace Domain::GetTodosUseCase;

GetTodosUseCase::GetTodosUseCase(GetTodosUseCaseRepositoryInterface& repo) : repo(repo) {}

std::vector<Task> GetTodosUseCase::get() const {
	return this->repo.get();
}