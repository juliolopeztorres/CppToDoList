#pragma once
#include "CreateTodoUseCase.h"

using namespace Domain::CreateTodoUseCase;

CreateTodoUseCase::CreateTodoUseCase(CreateTodoUseCaseRepositoryInterface& repo) : repo(repo) {}

void CreateTodoUseCase::create(const Task& task) const {
	this->repo.create(task);
}
